#include "graph.h"
#include <map>
#include <vector>
#include <string>
#include <fstream>
#define NATION_COUNT 200 // placeholder if we use vectors

// List of Variables :
// t: year
// i: exporter
// j: importer
// k: product
// v: value 
// q: quantity

Graph::Graph(const std::string& db_fpath) {
	for (uint x = 0; x <= 237; x++) {
		std::vector<int> tmpvect;
		for (uint y = 0; y <= 237; y++) {
			tmpvect.push_back(0);
		}
		graph.push_back(tmpvect);
	}

    std::string line;
	std::ifstream db(db_fpath);
	while(getline(db, line, '\n')) {
		size_t pos;
		std::string token;
		int exporter, importer;
		float productVal;
		unsigned count = 0;
		while((pos = line.find(',')) != std::string::npos) {
			token = line.substr(0, pos);
			if (count != 1 && count != 2 && count != 4) {
				line.erase(0, pos + 1);
				count++;
				continue;
			}
			if(count == 1)
				exporter = countrycodes(stoi(token));
			if(count == 2)
				importer = countrycodes(stoi(token));
            		if(count == 4)
                		productVal = stof(token);

			line.erase(0, pos + 1);
			count++;	
		}
		graph[exporter][importer] += productVal;
	}
}

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
}
