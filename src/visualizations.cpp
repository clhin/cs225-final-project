#include <string>
#include <vector>
#include <matplot/matplot.h>


void visualization::balanceOfTradeMap(int country, graph *&g){
    std::string inName = getCountryName(country);
    std::vector<float> inCoords = getCountryCoords(country);

    for(unsigned i = 0; i < g[country].size(); i++){
        if(g[country][i] != 0 && g[i][country] != 0){
            float tradeBalance = g[country][i] - g[i][country];
            std::string outName = getCountryName(g[country][i]);
            std::vector<float> outCoords = getCountryCoords(g[country][i]);

            geoplot(inCoords, outCoords, "b-");
            hold(on);
            text(outCoords[0], outCoords[1], outName);
        }
    }

    text(inCoords[0], inCoords[1], inName);
    show();

}


std::string visualization::getCountryName(int index){
    std::vector<string> names = {
        "Afghanistan","Albania","Algeria","American Samoa","Andorra","Angola","Antigua and Barbuda","Azerbaijan","Argentina","Australia","Austria","Bahamas","Bahrain","Bangladesh",
        "Armenia","Barbados","Belgium","Belgium-Luxembourg","Bermuda","Bhutan","Plurinational State of Bolivia","Bosnia Herzegovina","Botswana","Brazil","Belize","British Indian Ocean Territories",
        "Solomon Islands","British Virgin Islands","Brunei Darussalam","Bulgaria","Myanmar","Burundi","Belarus","Cambodia","Cameroon","Canada","Cabo Verde","Cayman Islands","Central African Republic",
        "Sri Lanka","Chad","Chile","China","Christmas Islands","Cocos Islands","Colombia","Comoros","Mayotte","Congo","Democratic Republic of the Congo","Cook Islands","Costa Rica","Croatia","Cuba",
        "Cyprus","Czechoslovakia","Czechia","Benin","Denmark","Dominica","Dominican Republic","Ecuador","El Salvador","Equatorial Guinea","Ethiopia","Eritrea","Estonia","Falkland Islands (Malvinas)",
        "Fiji","Finland","France, Monaco","French Polynesia","French South Antarctic Territories","Djibouti","Gabon","Georgia","Gambia","State of Palestine","Germany","Former Democratic Republic of Germany",
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
    }
    return names[i];
}

std::vector<float> visualization::getCountryCoords(int index){
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
        }

    return coords[i];
    

}