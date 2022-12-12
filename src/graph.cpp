#include "graph.h"
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

// List of Variables  as they are stored in the CSV
// t: year
// i: exporter
// j: importer
// k: product
// v: value 
// q: quantity

Graph::Graph() { //Used purely for testing purposes since hard to test and interpert with very large graph 
	return;
}

//Takes csv file input of the trade data and constructs the vector of vectors graph; an adjacency matrix
Graph::Graph(const std::string& db_fpath) {
	//initializes all points on matrix to zero
	for (uint x = 0; x <= 237; x++) {
		std::vector<float> tmpvect;
		for (uint y = 0; y <= 237; y++) {
			tmpvect.push_back(0);
		}
		graph.push_back(tmpvect);
	}
	int lineCount = 0;
    std::string line;
	std::ifstream db(db_fpath);
	//parses through each line of the csv
	while(getline(db, line, '\n')) {
		size_t pos;
		std::string token;
		int exporter, importer;
		float productVal;
		unsigned count = 0;
		//parses a row of the csv and gets the correct columns to be summed
		while((pos = line.find(',')) != std::string::npos) {
			token = line.substr(0, pos);
			if (count != 1 && count != 2 && count != 4) {
				line.erase(0, pos + 1);
				count++;
				continue;
			}
			if(lineCount != 0){
				if(count == 1)
					exporter = countrycodes(std::stoi(token));
				if(count == 2)
					importer = countrycodes(std::stoi(token));
            	if(count == 4)
            		productVal = std::stof(token);
			}

			line.erase(0, pos + 1);
			count++;	
		}
		//sums each item to get the
		if(lineCount != 0)
			graph[exporter][importer] += productVal;
		lineCount++;
	}
}

//This is a helper function used in testing
float Graph::Exports(int exporter, int importer){
	int normExporter = countrycodes(exporter);
	int normImporter = countrycodes(importer);
	if (normExporter == -1 || normImporter == -1)
		return -1;
	return graph[normExporter][normImporter];
}

/* A function that runs a BFS traversal of the graph starting from a given start point.
Inputs: The starting country code, given as an int
Outputs: A vector containing the BFS traversal order of the graph, full of country codes.
*/
std::vector<int> Graph::BFS(int start){
	std::queue<int> bfsq; //queue to keep track of the traversal.
	bfsq.push(start); //loading the queue with the first point.

	std::vector<int> traversal;//vector that contains the traversal history.

	std::vector<bool> visited(graph.size(), false); //vector that keeps track of the history of points visited.
	visited[start] = true; //marking the first point as visited.

	while(!bfsq.empty()){ //loop that traverses every point, marking each as visited, and saving the order in the traversal vector.
		int curr = bfsq.front();
		bfsq.pop();
		traversal.push_back(curr);

		for(unsigned long i = 0; i < graph[curr].size(); i++){
			if(!visited[i]){
				if(graph[curr][i] != 0){
					bfsq.push(i);
					visited[i] = true;
				}
			}
		}
	}
	return traversal;
}
//Given a country code, returns the approximate trade price to all other countries represented in a vector. We assume that trade price is inversly proptional to dollar amount of exports between countries
std::vector<float> Graph::Djikstra(int idx) { 
	std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> inverse_pq;
	int key_row = idx; //Gets the row we need to go to on matrix based on country code passed
	std::vector<float>vect_dist;
	inverse_pq.push({0,key_row}); //Start off by adding dist of 0 as well as our start node represented as index to priority que
	for (size_t x = 0; x < graph.size(); x++) { //Set all distances to maximum value in C++
		vect_dist.push_back(FLT_MAX); //Included in .h file
	}
	vect_dist[key_row] = 0; //Set dist at start (key_row for now to 0)
	while(!inverse_pq.empty()) {
		float dist = inverse_pq.top().first;
		int node = inverse_pq.top().second;
		key_row = node;
		for (size_t col = 0; col < graph[0].size(); col++) { //Based on what node (or row we have to go to on matrix), iiterate across row
			if (graph[key_row][col] != 0 && ((1/graph[key_row][col]) + dist) < vect_dist[col]) { //As we itterate ensure that val isn't 0 and dist calculated to go that node < what's currently present
				vect_dist[col] = 1/graph[key_row][col] + dist; //update the distance
				inverse_pq.push({vect_dist[col], col});
			}
		}
		inverse_pq.pop(); //remove top elemnt
	}
	return vect_dist;
}

std::vector<float> Graph::TestDjikstra(int idx, std::vector<std::vector<float>> test_graph) { //Used purely for testing purposes since hard to test + interpert on large graph
	std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> inverse_pq;
	int key_row = idx; //Gets the row we need to go to on matrix based on country code passed
	std::vector<float>vect_dist;
	inverse_pq.push({0,key_row}); //Start off by adding dist of 0 as well as our start node represented as index to priority que
	for (size_t x = 0; x < test_graph.size(); x++) { //Set all distances to maximum value in C++
		vect_dist.push_back(FLT_MAX); //Included in .h file
	}
	vect_dist[key_row] = 0; //Set dist at start (key_row for now to 0)
	while(!inverse_pq.empty()) {
		float dist = inverse_pq.top().first;
		key_row = inverse_pq.top().second;
		for (size_t col = 0; col < test_graph[0].size(); col++) { //Based on what node (or row we have to go to on matrix), iiterate across row
			if (test_graph[key_row][col] != 0 && ((1/test_graph[key_row][col]) + dist) < vect_dist[col]) { //As we itterate ensure that val isn't 0 and dist calculated to go that node < what's currently present
				vect_dist[col] = 1/test_graph[key_row][col] + dist; //update the distance
				inverse_pq.push({vect_dist[col], col});
			}
		}
		inverse_pq.pop(); //remove top elemnt
	}
	return vect_dist;
}


std::vector<float> Graph::pagerank(int iterations) {
	//this represents the probability that a traversal will stop, in our case
	//it is when a country stops trading
	double dampeningfactor = 0.82;
	int size = graph.size();
	std::vector<float> currentpagerank, inlinks(size, 0), outlinks(size, 0);
	for (uint row = 0; row < graph.size(); row++) {
		for (uint col = 0; col < graph.at(row).size(); col++) {
			//find our inlinks and outlinks count
			if (graph.at(row).at(col) != 0) {
				outlinks.at(row)++;
				inlinks.at(col)++;
			}
		}
	}
	// build the initial rank, a rule of thumb to maintain a pagerank is that all
	// elements should sum to 1
	for (uint row = 0; row < graph.size(); row++) {
			currentpagerank.push_back(1/size);
	}
	// iterations can be adjusted, more iterations = more accurate rank
	// this is also where the algorithm proper starts
	while (iterations > 0) {
		float rank = 0;
		std::vector<float> newpagerank(currentpagerank.size(), 0);
		//this loop is for the pageranks of dangling links
		for (uint i = 0; i < outlinks.size(); i++) {
			if (outlinks.at(i) == 0)
				rank = rank + dampeningfactor * 1.0 * currentpagerank.at(i)/size;
		}
		for (uint row = 0; row < graph.size(); row++) {
			newpagerank.at(row) = rank + (1-dampeningfactor)/size; //randomly jump pagerank
			for (uint i = 0; i < inlinks[row]; i++) {
				//make sure we aren't divinding by zero;
				if (outlinks.at(i) == 0)
					continue;
				//get pagerank of inlinks
				newpagerank.at(row) = newpagerank.at(row) + (1.0 * dampeningfactor*currentpagerank.at(i))/outlinks.at(i);
			}
		}
		currentpagerank = newpagerank; //update the rank
		iterations--;
	}
	return currentpagerank;
}

//Takes in the output of Page rank and a country, and returns the top three ranked countries the input country trades with
std::vector<int> Graph::pageranksearch(int country, std::vector<float> rank) {
	
	std::vector<int> searchresult;
	std::vector<std::pair<float,int>> pair;
	for (uint i = 0; i < graph.at(country).size(); i++) {
		if (graph.at(country).at(i) == 0)
			continue;
		pair.push_back(std::pair<float,int>(rank.at(i),i));
	}
	std::sort(pair.begin(), pair.end());
	searchresult.push_back(pair.at(pair.size()-1).second);
	searchresult.push_back(pair.at(pair.size()-2).second);
	searchresult.push_back(pair.at(pair.size()-3).second);
	return searchresult;
}


//Takes a country as a string and returns it's node index, used for terminal input
int stringToIdx(std::string country){
	std::vector<std::string> names = {
        "Afghanistan","Albania","Algeria","American Samoa","Andorra","Angola","Antigua and Barbuda","Azerbaijan","Argentina","Australia","Austria","Bahamas","Bahrain","Bangladesh",
        "Armenia","Barbados","Belgium","Belgium-Luxembourg","Bermuda","Bhutan","Plurinational State of Bolivia","Bosnia Herzegovina","Botswana","Brazil","Belize","British Indian Ocean Territories",
        "Solomon Islands","British Virgin Islands","Brunei Darussalam","Bulgaria","Myanmar","Burundi","Belarus","Cambodia","Cameroon","Canada","Cabo Verde","Cayman Islands","Central African Republic",
        "Sri Lanka","Chad","Chile","China","Christmas Islands","Cocos Islands","Colombia","Comoros","Mayotte","Congo","Democratic Republic of the Congo","Cook Islands","Costa Rica","Croatia","Cuba",
        "Cyprus","Czechoslovakia","Czechia","Benin","Denmark","Dominica","Dominican Republic","Ecuador","El Salvador","Equatorial Guinea","Ethiopia","Eritrea","Estonia","Falkland Islands (Malvinas)",
        "Fiji","Finland","France", "Monaco","French Polynesia","French South Antarctic Territories","Djibouti","Gabon","Georgia","Gambia","State of Palestine","Germany","Former Democratic Republic of Germany",
        "Former Federal Republic of Germany","Ghana","Gibraltar","Kiribati","Greece","Greenland","Grenada","Guam","Guatemala","Guinea","Guyana","Haiti","Honduras","China, Hong Kong Special Administrative Region",
        "Hungary","Iceland","Indonesia","Iran","Iraq","Ireland","Israel","Italy","CÙte d'Ivoire","Jamaica","Japan","Kazakhstan","Jordan","Kenya","Democratic People's Republic of Korea","Republic of Korea",
        "Kuwait","Kyrgyzstan","Lao People's Dem. Rep.","Lebanon","Lesotho","Latvia","Liberia","Libya","Lithuania","Luxembourg","China, Macao Special Administrative Region","Madagascar","Malawi","Malaysia",
        "Maldives","Mali","Malta","Mauritania","Mauritius","Mexico","Other Asia, not elsewhere specified","Mongolia","Republic of Moldova","Montenegro","Montserrat","Morocco","Mozambique","Oman","Namibia",
        "Nauru","Nepal","Netherlands","Netherlands Antilles","CuraÁao","Aruba","Saint Maarten (Dutch part)","Bonaire, Saint Eustatius and Saba","New Caledonia","Vanuatu","New Zealand","Nicaragua","Niger",
        "Nigeria","Niue","Norfolk Islands","Norway, Svalbard and Jan Mayen","Northern Mariana Islands","Federated State of Micronesia","Marshall Islands","Palau","Pakistan","Panama","Papua New Guinea","Paraguay",
        "Peru","Philippines","Pitcairn","Poland","Portugal","Guinea-Bissau","Timor-Leste","Qatar","Romania","Russian Federation","Rwanda","Saint BarthÈlemy","Saint Helena","Saint Kitts and Nevis","Anguilla",
        "Saint Lucia","Saint Pierre and Miquelon","Saint Vincent and the Grenadines","San Marino","Sao Tome and Principe","Saudi Arabia","Senegal","Serbia","Seychelles","Sierra Leone",
        "Europe EFTA, not elsewhere specified","India","Singapore","Slovakia","Viet Nam","Slovenia","Somalia","South Africa","Southern African Customs Union","Zimbabwe","Spain","South Sudan","Sudan",
        "Former Sudan","Suriname","Swaziland","Sweden","Switzerland, Liechtenstein","Syria","Tajikistan","Thailand","Togo","Tokelau","Tonga","Trinidad and Tobago","United Arab Emirates","Tunisia","Turkey",
        "Turkmenistan","Turks and Caicos Islands","Tuvalu","Uganda","Ukraine","The Former Yugoslav Republic of Macedonia","Former USSR","Egypt","United Kingdom","United Republic of Tanzania",
        "USA, Puerto Rico and US Virgin Islands","US Miscellaneous Pacific Islands","Burkina Faso","Uruguay","Uzbekistan","Venezuela","Wallis and Futuna Islands","Samoa","Yemen","Serbia and Montenegro","Zambia"
    };

	auto it = find(names.begin(), names.end(), country);

	if(it != names.end()){
		int index = it - names.begin();
		return index;
	}
	else{
		return -1;
	}
		
}

//Takes in a vector of country indicies and returns a vector of their string names, used for terminal output
std::vector<std::string> idxVectToString(std::vector<int> countryIdxs){
	std::vector<std::string> output;

	for(unsigned i = 0; i < countryIdxs.size(); i++)
		output.push_back(getCountryName(countryIdxs[i]));
		
	return output;
}

//takes the country's node index and returns its name as a string
std::string getCountryName(int index){
    std::vector<std::string> names = {
        "Afghanistan","Albania","Algeria","American Samoa","Andorra","Angola","Antigua and Barbuda","Azerbaijan","Argentina","Australia","Austria","Bahamas","Bahrain","Bangladesh",
        "Armenia","Barbados","Belgium","Belgium-Luxembourg","Bermuda","Bhutan","Plurinational State of Bolivia","Bosnia Herzegovina","Botswana","Brazil","Belize","British Indian Ocean Territories",
        "Solomon Islands","British Virgin Islands","Brunei Darussalam","Bulgaria","Myanmar","Burundi","Belarus","Cambodia","Cameroon","Canada","Cabo Verde","Cayman Islands","Central African Republic",
        "Sri Lanka","Chad","Chile","China","Christmas Islands","Cocos Islands","Colombia","Comoros","Mayotte","Congo","Democratic Republic of the Congo","Cook Islands","Costa Rica","Croatia","Cuba",
        "Cyprus","Czechoslovakia","Czechia","Benin","Denmark","Dominica","Dominican Republic","Ecuador","El Salvador","Equatorial Guinea","Ethiopia","Eritrea","Estonia","Falkland Islands (Malvinas)",
        "Fiji","Finland","France", "Monaco","French Polynesia","French South Antarctic Territories","Djibouti","Gabon","Georgia","Gambia","State of Palestine","Germany","Former Democratic Republic of Germany",
        "Former Federal Republic of Germany","Ghana","Gibraltar","Kiribati","Greece","Greenland","Grenada","Guam","Guatemala","Guinea","Guyana","Haiti","Honduras","China, Hong Kong Special Administrative Region",
        "Hungary","Iceland","Indonesia","Iran","Iraq","Ireland","Israel","Italy","CÙte d'Ivoire","Jamaica","Japan","Kazakhstan","Jordan","Kenya","Democratic People's Republic of Korea","Republic of Korea",
        "Kuwait","Kyrgyzstan","Lao People's Dem. Rep.","Lebanon","Lesotho","Latvia","Liberia","Libya","Lithuania","Luxembourg","China, Macao Special Administrative Region","Madagascar","Malawi","Malaysia",
        "Maldives","Mali","Malta","Mauritania","Mauritius","Mexico","Other Asia, not elsewhere specified","Mongolia","Republic of Moldova","Montenegro","Montserrat","Morocco","Mozambique","Oman","Namibia",
        "Nauru","Nepal","Netherlands","Netherlands Antilles","CuraÁao","Aruba","Saint Maarten (Dutch part)","Bonaire, Saint Eustatius and Saba","New Caledonia","Vanuatu","New Zealand","Nicaragua","Niger",
        "Nigeria","Niue","Norfolk Islands","Norway, Svalbard and Jan Mayen","Northern Mariana Islands","Federated State of Micronesia","Marshall Islands","Palau","Pakistan","Panama","Papua New Guinea","Paraguay",
        "Peru","Philippines","Pitcairn","Poland","Portugal","Guinea-Bissau","Timor-Leste","Qatar","Romania","Russian Federation","Rwanda","Saint BarthÈlemy","Saint Helena","Saint Kitts and Nevis","Anguilla",
        "Saint Lucia","Saint Pierre and Miquelon","Saint Vincent and the Grenadines","San Marino","Sao Tome and Principe","Saudi Arabia","Senegal","Serbia","Seychelles","Sierra Leone",
        "Europe EFTA, not elsewhere specified","India","Singapore","Slovakia","Viet Nam","Slovenia","Somalia","South Africa","Southern African Customs Union","Zimbabwe","Spain","South Sudan","Sudan",
        "Former Sudan","Suriname","Swaziland","Sweden","Switzerland, Liechtenstein","Syria","Tajikistan","Thailand","Togo","Tokelau","Tonga","Trinidad and Tobago","United Arab Emirates","Tunisia","Turkey",
        "Turkmenistan","Turks and Caicos Islands","Tuvalu","Uganda","Ukraine","The Former Yugoslav Republic of Macedonia","Former USSR","Egypt","United Kingdom","United Republic of Tanzania",
        "USA, Puerto Rico and US Virgin Islands","US Miscellaneous Pacific Islands","Burkina Faso","Uruguay","Uzbekistan","Venezuela","Wallis and Futuna Islands","Samoa","Yemen","Serbia and Montenegro","Zambia"
    };
	if(index < 238)
    	return names[index];
	std::cout<<"Not a Valid Country Index: "<<index<<std::endl;
		return "-1";
}

//Takes an index and returns a latitude and longitude, used for visualizations
std::vector<float> getCountryCoords(int index){
    std::vector<std::vector<float > > coords = {
        {33.93911,67.709953},{41.153332,20.168331},{28.033886,1.659626},{-14.270972,-170.132217},{42.546245,1.601554},{-11.202692,17.873887},{17.060816,-61.796428},{40.143105,47.576927},
        {-38.416097,-63.616672},{-25.274398,133.775136},{47.516231,14.550072},{25.03428,-77.39628},{25.930414,50.637772},{23.684994,90.356331},{40.069099,45.038189},{13.193887,-59.543198},
        {50.503887,4.469936},{50.503887,4.469936},{32.321384,-64.75737},{27.514162,90.433601},{-16.290154,-63.588653},{43.915886,17.679076},{-22.328474,24.684866},{-14.235004,-51.92528},
        {17.189877,-88.49765},{-6.343194,71.876519},{-9.64571,160.156194},{18.420695,-64.639968},{4.535277,114.727669},{42.733883,25.48583},{21.913965,95.956223},{-3.373056,29.918886},
        {53.709807,27.953389},{12.565679,104.990963},{7.369722,12.354722},{56.130366,-106.346771},{16.002082,-24.013197},{19.513469,-80.566956},{6.611111,20.939444},{7.873054,80.771797},
        {15.454166,18.732207},{-35.675147,-71.542969},{35.86166,104.195397},{-10.447525,105.690449},{-12.164165,96.870956},{4.570868,-74.297333},{-11.875001,43.872219},{-12.8275,45.166244},
        {-0.228021,15.827659},{-4.038333,21.758664},{-21.236736,-159.777671},{9.748917,-83.753428},{45.1,15.2},{21.521757,-77.781167},{35.126413,33.429859},{14.480176,121.0392436},{49.817492,15.472962},
        {9.30769,2.315834},{56.26392,9.501785},{15.414999,-61.370976},{18.735693,-70.162651},{-1.831239,-78.183406},{13.794185,-88.89653},{1.650801,10.267895},{9.145,40.489673},{15.179384,39.782334},
        {58.595272,25.013607},{-51.796253,-59.523613},{-16.578193,179.414413},{61.92411,25.748151},{46.227638,2.213749},{-17.679742,-149.406843},{41.6351796,12.4441379},{11.825138,42.590275},
        {-0.803689,11.609444},{42.315407,43.356892},{13.443182,-15.310139},{31.952162,35.233154},{51.165691,10.451526},{51.165691,10.451526},{51.165691,10.451526},{7.946527,-1.023194},{36.137741,-5.345374},
        {-3.370417,-168.734039},{39.074208,21.824312},{71.706936,-42.604303},{12.262776,-61.604171},{13.444304,144.793731},{15.783471,-90.230759},{9.945587,-9.696645},{4.860416,-58.93018},{18.971187,-72.285215},
        {15.199999,-86.241905},{22.396428,114.109497},{47.162494,19.503304},{64.963051,-19.020835},{-0.789275,113.921327},{32.427908,53.688046},{33.223191,43.679291},{53.41291,-8.24389},{31.046051,34.851612},
        {41.87194,12.56738},{7.539989,-5.54708},{18.109581,-77.297508},{36.204824,138.252924},{48.019573,66.923684},{30.585164,36.238414},{-0.023559,37.906193},{40.339852,127.510093},{35.907757,127.766922},
        {29.31166,47.481766},{41.20438,74.766098},{19.85627,102.495496},{33.854721,35.862285},{-29.609988,28.233608},{56.879635,24.603189},{6.428055,-9.429499},{26.3351,17.228331},{55.169438,23.881275},
        {49.815273,6.129583},{22.198745,113.543873},{-18.766947,46.869107},{-13.254308,34.301525},{4.210484,101.975766},{3.202778,73.22068},{17.570692,-3.996166},{35.937496,14.375416},{21.00789,-10.940835},
        {-20.348404,57.552152},{23.634501,-102.552784},{15.4881,114.4048},{46.862496,103.846656},{47.411631,28.369885},{42.708678,19.37439},{16.742498,-62.187366},{31.791702,-7.09262},{-18.665695,35.529562},
        {21.512583,55.923255},{-22.95764,18.49041},{-0.522778,166.931503},{28.394857,84.124008},{52.132633,5.291266},{12.226079,-69.060087},{12.1176488,-68.9309263},{12.52111,-69.968338},{18.0423736,-63.0549948},
        {12.167,-68.2876439},{-20.904305,165.618042},{-15.376706,166.959158},{-40.900557,174.885971},{12.865416,-85.207229},{17.607789,8.081666},{9.081999,8.675277},{-19.054445,-169.867233},{-29.040835,167.954712},
        {60.472024,8.468946},{17.33083,145.38469},{7.425554,150.550812},{7.131474,171.184478},{7.51498,134.58252},{30.375321,69.345116},{8.537981,-80.782127},{-6.314993,143.95555},{-23.442503,-58.443832},
        {-9.189967,-75.015152},{12.879721,121.774017},{-24.703615,-127.439308},{51.919438,19.145136},{39.399872,-8.224454},{11.803749,-15.180413},{-8.874217,125.727539},{25.354826,51.183884},{45.943161,24.96676},
        {61.52401,105.318756},{-1.940278,29.873888},{17.9036287,-62.8115292},{-24.143474,-10.030696},{17.357822,-62.782998},{18.220554,-63.068615},{13.909444,-60.978893},{46.941936,-56.27111},{12.984305,-61.287228},
        {43.94236,12.457777},{0.18636,6.613081},{23.885942,45.079162},{14.497401,-14.452362},{44.016521,21.005859},{-4.679574,55.491977},{8.460555,-11.779889},{34.5531,18.0480},{20.593684,78.96288},
        {1.352083,103.819836},{48.669026,19.699024},{14.058324,108.277199},{46.151241,14.995463},{5.152149,46.199616},{-30.559482,22.937506},{-30.559482,22.937506},{-19.015438,29.154857},{40.463667,-3.74922},
        {7.8699431,29.6667897},{12.862807,30.217636},{12.862807,30.217636},{3.919305,-56.027783},{-26.522503,31.465866},{60.128161,18.643501},{46.818188,8.227512},{34.802075,38.996815},{38.861034,71.276093},
        {15.870032,100.992541},{8.619543,0.824782},{-8.967363,-171.855881},{-21.178986,-175.198242},{10.691803,-61.222503},{23.424076,53.847818},{33.886917,9.537499},{38.963745,35.243322},{38.969719,59.556278},
        {21.694025,-71.797928},{-7.109535,177.64933},{1.373333,32.290275},{48.379433,31.16558},{41.608635,21.745275},{55.7504461,37.6174943},{26.820553,30.802498},{55.378051,-3.435973},{-6.369028,34.888822},
        {37.09024,-95.712891},{15.18333,145.75},{12.238333,-1.561593},{-32.522779,-55.765835},{41.377491,64.585262},{6.42375,-66.58973},{-13.768752,-177.156097},{-13.759029,-172.104629},{15.552727,48.516388},
        {44.1534121,20.55144},{-13.133897,27.849332}
        };

	if(index < 238)
    	return coords[index];
	std::cout<<"Not a Valid Country Index"<<std::endl;
		return std::vector<float>{-1, -1};
    
}



//takes country code input as an int and returns the enumerated value of the country, ie the position in the vectors in each node
int Graph::countrycodes(int i){
	switch (i){
		case 4: return 0;
		case 8: return 1;
		case 12: return 2;
		case 16: return 3;
		case 20: return 4;
		case 24: return 5;
		case 28: return 6;
		case 31: return 7;
		case 32: return 8;
		case 36: return 9;
		case 40: return 10;
		case 44: return 11;
		case 48: return 12;
		case 50: return 13;
		case 51: return 14;
		case 52: return 15;
		case 56: return 16;
		case 58: return 17;
		case 60: return 18;
		case 64: return 19;
		case 68: return 20;
		case 70: return 21;
		case 72: return 22;
		case 76: return 23;
		case 84: return 24;
		case 86: return 25;
		case 90: return 26;
		case 92: return 27;
		case 96: return 28;
		case 100: return 29;
		case 104: return 30;
		case 108: return 31;
		case 112: return 32;
		case 116: return 33;
		case 120: return 34;
		case 124: return 35;
		case 132: return 36;
		case 136: return 37;
		case 140: return 38;
		case 144: return 39;
		case 148: return 40;
		case 152: return 41;
		case 156: return 42;
		case 162: return 43;
		case 166: return 44;
		case 170: return 45;
		case 174: return 46;
		case 175: return 47;
		case 178: return 48;
		case 180: return 49;
		case 184: return 50;
		case 188: return 51;
		case 191: return 52;
		case 192: return 53;
		case 196: return 54;
		case 200: return 55;
		case 203: return 56;
		case 204: return 57;
		case 208: return 58;
		case 212: return 59;
		case 214: return 60;
		case 218: return 61;
		case 222: return 62;
		case 226: return 63;
		case 231: return 64;
		case 232: return 65;
		case 233: return 66;
		case 238: return 67;
		case 242: return 68;
		case 246: return 69;
		case 251: return 70;
		case 258: return 71;
		case 260: return 72;
		case 262: return 73;
		case 266: return 74;
		case 268: return 75;
		case 270: return 76;
		case 275: return 77;
		case 276: return 78;
		case 278: return 79;
		case 280: return 80;
		case 288: return 81;
		case 292: return 82;
		case 296: return 83;
		case 300: return 84;
		case 304: return 85;
		case 308: return 86;
		case 316: return 87;
		case 320: return 88;
		case 324: return 89;
		case 328: return 90;
		case 332: return 91;
		case 340: return 92;
		case 344: return 93;
		case 348: return 94;
		case 352: return 95;
		case 360: return 96;
		case 364: return 97;
		case 368: return 98;
		case 372: return 99;
		case 376: return 100;
		case 381: return 101;
		case 384: return 102;
		case 388: return 103;
		case 392: return 104;
		case 398: return 105;
		case 400: return 106;
		case 404: return 107;
		case 408: return 108;
		case 410: return 109;
		case 414: return 110;
		case 417: return 111;
		case 418: return 112;
		case 422: return 113;
		case 426: return 114;
		case 428: return 115;
		case 430: return 116;
		case 434: return 117;
		case 440: return 118;
		case 442: return 119;
		case 446: return 120;
		case 450: return 121;
		case 454: return 122;
		case 458: return 123;
		case 462: return 124;
		case 466: return 125;
		case 470: return 126;
		case 478: return 127;
		case 480: return 128;
		case 484: return 129;
		case 490: return 130;
		case 496: return 131;
		case 498: return 132;
		case 499: return 133;
		case 500: return 134;
		case 504: return 135;
		case 508: return 136;
		case 512: return 137;
		case 516: return 138;
		case 520: return 139;
		case 524: return 140;
		case 528: return 141;
		case 530: return 142;
		case 531: return 143;
		case 533: return 144;
		case 534: return 145;
		case 535: return 146;
		case 540: return 147;
		case 548: return 148;
		case 554: return 149;
		case 558: return 150;
		case 562: return 151;
		case 566: return 152;
		case 570: return 153;
		case 574: return 154;
		case 579: return 155;
		case 580: return 156;
		case 583: return 157;
		case 584: return 158;
		case 585: return 159;
		case 586: return 160;
		case 591: return 161;
		case 598: return 162;
		case 600: return 163;
		case 604: return 164;
		case 608: return 165;
		case 612: return 166;
		case 616: return 167;
		case 620: return 168;
		case 624: return 169;
		case 626: return 170;
		case 634: return 171;
		case 642: return 172;
		case 643: return 173;
		case 646: return 174;
		case 652: return 175;
		case 654: return 176;
		case 659: return 177;
		case 660: return 178;
		case 662: return 179;
		case 666: return 180;
		case 670: return 181;
		case 674: return 182;
		case 678: return 183;
		case 682: return 184;
		case 686: return 185;
		case 688: return 186;
		case 690: return 187;
		case 694: return 188;
		case 697: return 189;
		case 699: return 190;
		case 702: return 191;
		case 703: return 192;
		case 704: return 193;
		case 705: return 194;
		case 706: return 195;
		case 710: return 196;
		case 711: return 197;
		case 716: return 198;
		case 724: return 199;
		case 728: return 200;
		case 729: return 201;
		case 736: return 202;
		case 740: return 203;
		case 748: return 204;
		case 752: return 205;
		case 757: return 206;
		case 760: return 207;
		case 762: return 208;
		case 764: return 209;
		case 768: return 210;
		case 772: return 211;
		case 776: return 212;
		case 780: return 213;
		case 784: return 214;
		case 788: return 215;
		case 792: return 216;
		case 795: return 217;
		case 796: return 218;
		case 798: return 219;
		case 800: return 220;
		case 804: return 221;
		case 807: return 222;
		case 810: return 223;
		case 818: return 224;
		case 826: return 225;
		case 834: return 226;
		case 842: return 227;
		case 849: return 228;
		case 854: return 229;
		case 858: return 230;
		case 860: return 231;
		case 862: return 232;
		case 876: return 233;
		case 882: return 234;
		case 887: return 235;
		case 891: return 236;
		case 894: return 237;

	}
	return -1;
}
