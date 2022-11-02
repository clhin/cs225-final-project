#include "graph.hpp"

Graph::Graph(const std::string& db_fpath) {
	std::string line;
	// create an empty matrix to start with
	for (uint x = 0; x < 190; x++) {
		std::vector<int> tmpvect;
		for (uint y = 0; y < 190; y++) {
			tmpvect.push_back(0);
		}
		graph.push_back(tmpvect);
	} 
	std::ifstream db(db_fpath);
	while (std::getline(db, line, '\n')) {
		int count = 0, x = -1, y = -1;
		size_t pos;
		std::string token;
		while((pos = line.find(',')) != std::string::npos) {
			// we only care about two lines, country and group
			token = line.substr(0, pos);
			if (count != 7 && count != 58) {
				line.erase(0, pos + 1);
				count++;
				continue;
			}
			if (count == 7) {
				x = countrycodes(stoi(token));
			}
			if (count == 58) {
				y = terrorcodes(token);
			}
			line.erase(0, pos + 1);
			count++;	
		}
		if (x >= 0 && y >= 0)
			graph[x][y]++;
	}
}

int Graph::countrycodes(int i) {
	switch (i) {
		case 4:
			return AFGHANISTAN;
		case 5:
			return ALBANIA;
		case 6:
			return ALGERIA;
		case 7:
			return ANDORRA;
		case 8:
			return ANGOLA;
		case 10:
			return ANTIGUABARBUDA;
		case 11:
			return ARGENTINA;
		case 12:
			return ARMENIA;	
		case 14:
			return AUSTRALIA;
		case 15:
			return AUSTRIA;
		case 16:
			return AZERBAIJAN;
		case 17:
			return BAHAMAS;
		case 18:
			return BAHRAIN;
		case 19:
			return BANGLADESH;
		case 20:
			return BARBADOS;
		case 21:
			return BELGIUM;
		case 22:
			return BELIZE;
		case 23:
			return BENIN;
		case 24:
			return UNITEDKINGDOM;
		case 25:
			return BHUTAN;
		case 26:
			return BOLIVIA;
		case 28:
			return BOSNIAHERZEGOVNIA;
		case 29:
			return BOTSWANA;
		case 30:
			return BRAZIL;
		case 31:
			return BRUNEI;
		case 32:
			return BULGARIA;
		case 33:
			return BURKINAFASO;
		case 34:
			return BURUNDI;
		case 35:
			return BELARUS;
		case 36:
			return CAMBODIA;
		case 37:
			return CAMEROON;
		case 38:
			return CANADA;
		case 41:
			return CENTRALAFRICANREPUBLIC;
		case 42:
			return CHAD;
		case 43:
			return CHILE;
		case 44:
			return CHINA;
		case 45:
			return COLOMBIA;
		case 46:
			return COMOROS;
		case 47:
			return REPUBLICOFCONGO;
		case 49:
			return COSTARICA;
		case 50:
			return CROATIA;
		case 51:
			return CUBA;
		case 53:
			return CYPRUS;
		case 54:
			return CZECHREPUBLIC;
		case 55:
			return DENMARK;
		case 56:
			return DJIBOUTI;
		case 57:
			return DOMINICA;
		case 58:
			return DOMINICANREPUBLIC;
		case 59:
			return ECUADOR;
		case 60:
			return EGYPT;
		case 61:
			return ELSALVADOR;
		case 62:
			return EQUATORIALGUINEA;
		case 63:
			return ERITREA;
		case 64:
			return ESTONIA;
		case 65:
			return ETHIOPIA;
		case 66:
			return FALKLANDISLANDS;
		case 67:
			return FIJI;
		case 68:
			return FINLAND;
		case 69:
		case 70:
		case 71:
			return FRANCE;
		case 72:
			return GABON;
		case 73:
			return GAMBIA;
		case 74:
			return GEORGIA;
		case 75:
			return GERMANY;
		case 76:
			return GHANA;
		case 78:
			return GREECE;
		case 79:
			return DENMARK;
		case 80:
			return GRENADA;
		case 81:
			return GUADELOUPE;
		case 83:
			return GUATEMALA;
		case 84:
			return GUINEA;
		case 85:
			return GUINEABISSAU;
		case 86:
			return GUYANA;
		case 87:
			return HAITI;
		case 88:
			return HONDURAS;
		case 89:
			return CHINA;
		case 90:
			return HUNGARY;
		case 91:
			return ICELAND;
		case 92:
			return INDIA;
		case 93:
			return INDONESIA;
		case 94:
			return IRAN;
		case 95:
			return IRAQ;
		case 96:
			return IRELAND;
		case 97:
			return ISRAEL;
		case 98:
			return ITALY;
		case 99:
			return IVORYCOAST;
		case 100:
			return JAMAICA;
		case 101:
			return JAPAN;
		case 102:
			return JORDAN;
		case 103:
			return KAZAKHSTAN;
		case 104:
			return KENYA;
		case 106:
			return KUWAIT;
		case 107:
			return KYRGYZSTAN;
		case 108:
			return LAOS;
		case 109:
			return LATVIA;
		case 110:
			return LEBANON;
		case 111:
			return LESOTHO;
		case 112:
			return LIBERIA;
		case 113:
			return LIBYA;
		case 114:
			return LIECHTENSTIEN;
		case 115:
			return LITHUANIA;
		case 116:
			return LUXEMBOURG;
		case 117:
			return CHINA;
		case 118:
			return MACEDONIA;
		case 119:
			return MADAGASCAR;
		case 120:
			return MALAWI;
		case 121:
			return MALAYSIA;
		case 122:
			return MALDIVES;
		case 123:
			return MALI;
		case 124:
			return MALTA;
		case 125:
			return UNITEDKINGDOM;
		case 126:
			return UNITEDSTATES;
		case 127:
			return FRANCE;
		case 128:
			return MAURITANIA;
		case 129:
			return MAURITIUS;
		case 130:
			return MEXICO;
		case 132:
			return MOLDOVA;
		case 134:
			return MONGOLIA;
		case 136:
			return MOROCCO;
		case 137:
			return MOZAMBIQUE;
		case 138:
			return MYANMAR;
		case 139:
			return NAMIBIA;
		case 141:
			return NEPAL;
		case 142:
			return NETHERLANDS;
		case 143:
			return FRANCE;
		case 144:
			return NEWZEALAND;
		case 145:
			return NICARAGUA;
		case 146:
			return NIGER;
		case 147:
			return NIGERIA;
		case 149:
			return NORTHKOREA;
		case 151:
			return NORWAY;
		case 152:
			return OMAN;
		case 153:
			return PAKISTAN;
		case 155:
			return WESTBANKGAZASTRIP;
		case 156:
			return PANAMA;
		case 157:
			return PAPUANEWGUINEA;
		case 158:
			return PARAGUAY;
		case 159:
			return PERU;
		case 160:
			return PHILIPPINES;
		case 161:
			return POLAND;
		case 163:
			return UNITEDSTATES;
		case 164:
			return QATAR;
		case 166:
			return ROMANIA;
		case 167:
			return RUSSIA;
		case 168:
			return RWANDA;
		case 169:
			return NETHERLANDS;
		case 173:
			return SAUDIARABIA;
		case 174:
			return SENEGAL;
		case 175:
			return SERBIA;
		case 176:
			return SEYCHELLES;
		case 177:
			return SIERRALEONE;
		case 178:
			return SINGAPORE;
		case 179:
			return SLOVAKIA;
		case 180:
			return SLOVENIA;
		case 181:
			return UNITEDSTATES;
		case 182:
			return SOMALIA;
		case 183:
			return SOUTHAFRICA;
		case 184:
			return SOUTHKOREA;
		case 185:
			return SPAIN;
		case 186:
			return SRILANKA;
		case 189:
			return STKITTSNEVIS;
		case 190:
			return STLUCIA;
		case 192:
			return ITALY;
		case 195:
			return SUDAN;
		case 196:
			return SURINAME;
		case 197:
			return SWAZILAND;
		case 198:
			return SWEDEN;
		case 199:
			return SWITZERLAND;
		case 200:
			return SYRIA;
		case 201:
			return TAIWAN;
		case 202:
			return TAJIKISTAN;
		case 203:
			return TANZANIA;
		case 204:
			return TOGO;
		case 205:
			return THAILAND;
		case 206:
			return FIJI;
		case 207:
			return TRINIDADTOBAGO;
		case 208:
			return TUNISIA;
		case 209:
			return TURKEY;
		case 210:
			return TURKMENISTAN;
		case 212:
			return UNITEDKINGDOM;
		case 213:
			return UGANDA;
		case 214:
			return UKRAINE;
		case 215:
			return UNITEDARABEMIRATES;
		case 216:
			return UNITEDKINGDOM;
		case 217:
			return UNITEDSTATES;
		case 218:
			return URUGUAY;
		case 219:
			return UZBEKISTAN;
		case 220:
			return VANUATU;
		case 221:
			return VATICANCITY;
		case 222:
			return VENEZUELA;
		case 223:
			return VIETNAM;
		case 225:
			return UNITEDSTATES;
		case 226:
			return FRANCE;
		case 228:
			return YEMEN;
		case 229:
			return DRC;
		case 230:
			return ZAMBIA;
		case 231:
			return ZIMBABWE;
		case 233:
			return UNITEDKINGDOM;
		case 235:
			return YUGOSLAVIA;
		case 236:
			return CZECHOSLOVAKIA;
		case 238:
			return FRANCE;
		case 347:
			return EASTTIMOR;
		case 349:
			return MOROCCO;
		case 351:
		case 359:
			return RUSSIA;
		case 362:
			return GERMANY;
		case 377:
			return YEMEN;
		case 403:
			return ZIMBABWE;
		case 406:
			return YEMEN;
		case 428:
			return VIETNAM;
		case 499:
			return GERMANY;
		case 520:
			return INDIA;
		case 532:
			return VANUATU;
		case 603:
			return UNITEDKINGDOM;
		case 604:
			return DRC;
		case 605:
			return REPUBLICOFCONGO;
		case 1001:
			return SERBIA;
		case 1002:
			return MONTENEGRO;
		case 1003:
			return KOSOVO;
		case 1004:
			return SOUTHSUDAN;
		default:
			return -1;
	}
}


// note to implementor, to find what number to return, simply type the name of
// the country you found in all caps accoring to the spelling in countries.h
// this is an enum which aliases country names to their position in the ajacency
// matrix
//
// you will probably also have to write a very long if statement since switches
// refuse to take strings, I tried to do a hash as an experiment for this, but
// the compiled apparently doesn't like this as the hashing wasn't a constant at
// compile time (even though it totally was), maybe you could get around this
// with a preprocessor macro instead, there should be about 190 condition, make
// sure to use || and not make a case for every group...

//XXX implement me
int Graph::terrorcodes(std::string s) {
	std::string tmpstring = s;
	return -1;
}
