/*********************************************************************************
 * BSD 3-Clause License
 *
 * Copyright (c) 2019, baggio63446333
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************************/

#include "QZQSM_EN.h"

//===============================================================
// Private Functions
//===============================================================

//===============================================================
// Disaster Category Code 1
// JMA-DC Report (Earthquake Early Warning)

#ifdef QZQSM_ENABLE_DC1

#define DC1_REPORT "Disaster notification (emergency earthquake report) (%s)\n"

#define DC1_REPORT2 "%s\n"

#define DC1_REPORT3 \
  "\n" \
  "Announcement time: %d month %d day %d hour %d minute\n\n" \
  "Epicenter name: %s\n" \
  "Earthquake time: %d day %d hour %d minute\n" \
  "Depth (km): %s\n" \
  "magnitude: %s\n" \
  "Seismic intensity (lower limit): %s\n" \
  "Seismic intensity (upper limit): %s\n"

#define DC1_REPORT4 "%s\n"

#endif // QZQSM_ENABLE_DC1

#if defined(QZQSM_ENABLE_DC1) || defined(QZQSM_ENABLE_DC2) || defined(QZQSM_ENABLE_DC5)

// Notification on Disaster Prevention (Information)
const char* QZQSM::dc1co2str(int code)
{
   switch (code) {
   case 0: return "none";
   case 101: return "There may be some sea level changes in the future.";
   case 102: return "There may be some sea level changes in the future, but there is no concern about damage.";
   case 103: return "Sea level change is expected to continue for some time to come.";
   case 104: return "Sea level fluctuations are expected to continue for some time to come, so please be careful when swimming or surf fishing.";
   case 105: return "Sea level fluctuations are expected to continue for some time to come, so please be careful when surf fishing.";
   case 107: return "There are currently no major tsunami warnings, tsunami warnings, or tsunami advisories issued for any coastal areas.";
   case 109: return "If the tsunami and high tide overlap, the tsunami will be higher, so we need to be even more vigilant.";
   case 110: return "If the tsunami and high tide overlap, the tsunami will be higher, so be careful.";
   case 111: return "Depending on the location, a tsunami that is larger than the observed tsunami height may have reached.";
   case 112: return "In the future, the height of the tsunami may increase further.";
   case 113: return "The tsunami is estimated to have already reached the coastal areas where the tsunami is estimated based on offshore observations.";
   case 114: return "It may take several hours or more to observe the maximum wave after the tidal change due to the tsunami is observed.";
   case 115: return "This is an offshore observation, tsunamis will be higher inshore.";
   case 121: return "<Major Tsunami Warning>\n"
                    "　A large tsunami will hit and cause enormous damage.\n"
                    "People in coastal areas or along rivers should immediately evacuate to safer places such as high ground or evacuation buildings.\n"
                    "The tsunami will strike repeatedly. Please stay in a safe place until the warning is lifted.";
   case 122: return "<Tsunami Warning>\n"
                    "　Tsunami damage will occur.\n"
                    "People in coastal areas or along rivers should immediately evacuate to safer places such as high ground or evacuation buildings.\n"
                    "The tsunami will strike repeatedly. Please stay in a safe place until the warning is lifted.";
   case 123: return "<Tsunami Warning>\n"
                    "　It is dangerous in the sea or near the coast.\n"
                    "People in the sea should immediately get out of the sea and leave the coast.\n"
                    "Since the tide will continue to flow rapidly, please do not enter the sea or approach the coast until the advisory is lifted.";
   case 124: return "<Tsunami forecast (slight sea level change)>\n"
                    "Slight changes in sea level are expected, but there is no concern about damage.";
   case 131: return "People in coastal or riverside areas where the warning was announced should immediately evacuate to safer places such as high ground or evacuation buildings.\n"
                    "Estimated time of arrival is the earliest time the tsunami will arrive in the forecast area. Depending on the location, the tsunami may hit much later than this time.\n"
                    "It may take several hours or more for the tsunami to reach its peak from the estimated arrival time, so please stay in a safe place until the warning is lifted, regardless of the observed tsunami height.";
   case 132: return "Depending on the location, the tsunami height may be higher than the 'expected tsunami height'. ";
   case 141: return "A tsunami equivalent to the Great East Japan Earthquake will hit.";
   case 142: return "Since a high tsunami was observed offshore, it was switched to a major tsunami warning/tsunami warning.";
   case 143: return "Since a high tsunami was observed offshore, the major tsunami warning and tsunami warning were switched.";
   case 144: return "Since we observed a high tsunami offshore, we switched to a major tsunami warning.";
   case 145: return "Since a high tsunami was observed offshore, the major tsunami warning was switched.";
   case 146: return "Since a high tsunami was observed offshore, the tsunami warning has been activated.";
   case 147: return "The tsunami warning was switched because a high tsunami was observed offshore.";
   case 148: return "Switched expected tsunami height due to high tsunami observed offshore.";
   case 149: return "Please evacuate immediately.";
   case 201: return "Watch out for strong shaking.";
   case 211: return "A tsunami warning, etc. (major tsunami warning, tsunami warning, or tsunami advisory) is being issued.";
   case 212: return "Due to this earthquake, there may be some sea level fluctuations along the coast of Japan, but there is no concern about damage.";
   case 213: return "Sea level fluctuations are expected to continue for some time to come, so please be careful when swimming or surf fishing.";
   case 214: return "Sea level fluctuations are expected to continue for some time to come, so please be careful when surf fishing.";
   case 215: return "There is no tsunami from this earthquake.";
   case 216: return "If the epicenter is on the seabed, a tsunami may occur.";
   case 217: return "Please note future information.";
   case 221: return "There is a possibility of a tsunami occurring in a wide area of the Pacific Ocean.";
   case 222: return "There is a possibility of a tsunami occurring in the Pacific Ocean.";
   case 223: return "There is a possibility of a tsunami occurring in the Northwest Pacific.";
   case 224: return "There is a possibility of a tsunami occurring in a wide area of the Indian Ocean.";
   case 225: return "There is a possibility of a tsunami occurring in the Indian Ocean.";
   case 226: return "A tsunami may occur near the epicenter.";
   case 227: return "There is a possibility of a small tsunami near the epicenter, but there is no danger of a damaging tsunami.";
   case 228: return "In general, an earthquake of this magnitude in a shallow ocean area can cause a tsunami.";
   case 229: return "We are currently investigating whether a tsunami hit Japan.";
   case 230: return "There is no tsunami impact on Japan from this earthquake.";
   case 241: return "Earthquake Early Warning is issued for this earthquake.";
   case 242: return "An emergency earthquake warning has been issued for this earthquake. The maximum seismic intensity of this earthquake was 2.";
   case 243: return "An emergency earthquake warning has been issued for this earthquake. The maximum seismic intensity of this earthquake was 1.";
   case 244: return "Earthquake Early Warning has been issued for this earthquake. A seismic intensity of 1 or higher has not been observed for this earthquake.";
   case 245: return "Earthquake early warning was issued for this earthquake, but no strong shaking was observed.";
   case 256: return "Correct the source element.";
   case 500: return "Other emergency precautions";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Precautions for disaster prevention (code number: %d)", code);
     return _undefMessage;
   }
}
#endif // defined(QZQSM_ENABLE_DC1) || defined(QZQSM_ENABLE_DC2) || defined(QZQSM_ENABLE_DC5)

#if defined(QZQSM_ENABLE_DC1) || defined(QZQSM_ENABLE_DC2)

// Depth of Seismic Epicenter
const char* QZQSM::dc1de2str(int de)
{
   static char destr[8];
   if (511 == de) {
     return "unknown";
   } else if (501 <= de) {
     return "500 or more";
   } else {
     snprintf(destr, sizeof(destr), "%d", de);
     return destr;
   }
}

// Magnitude
const char* QZQSM::dc1ma2str(int ma)
{
  static char mastr[8];
  if (127 == ma) {
    return "unknown";
  } else if (101 <= ma) {
    return "10.0 or higher";
  } else {
    snprintf(mastr, sizeof(mastr), "%d.%d", ma / 10, ma % 10);
    return mastr;
  }
}

// Seismic Epicenter
const char* QZQSM::dc1ep2str(int code)
{
  switch (code) {
  case 11: return "Hokkaido region";
  case 12: return "Tohoku";
  case 13: return "Hokuriku";
  case 14: return "Kanto Koshin region";
  case 15: return "Ogasawara region";
  case 16: return "Tokai region";
  case 17: return "Kinki region";
  case 18: return "Chugoku region";
  case 19: return "Shikoku";
  case 20: return "Kyushu region";
  case 21: return "Okinawa region";
  case 100: return "Northern Ishikari";
  case 101: return "Central Ishikari";
  case 102: return "Southern Ishikari";
  case 105: return "Northern Oshima";
  case 106: return "Eastern Oshima";
  case 107: return "West Oshima";
  case 110: return "Hiyama region";
  case 115: return "Northern Shiribeshi";
  case 116: return "Eastern Shiribeshi";
  case 117: return "Western Shiribeshi";
  case 120: return "Northern Sorachi";
  case 121: return "Central Sorachi";
  case 122: return "Southern Sorachi";
  case 125: return "Northern Kamikawa";
  case 126: return "Central Kamikawa";
  case 127: return "Southern Kamikawa";
  case 130: return "Central North Rumoi";
  case 131: return "Southern Rumoi";
  case 135: return "Northern Soya";
  case 136: return "Southern Soya region";
  case 140: return "Abashiri region";
  case 141: return "Kitami";
  case 142: return "Monbetsu";
  case 145: return "Western Iburi";
  case 146: return "Middle Eastern Iburi";
  case 150: return "West Hidaka";
  case 151: return "Central Hidaka";
  case 152: return "Eastern Hidaka";
  case 155: return "Northern Tokachi";
  case 156: return "Central Tokachi";
  case 157: return "Southern Tokachi";
  case 160: return "Northern Kushiro";
  case 161: return "Central South Kushiro";
  case 165: return "Northern Nemuro";
  case 166: return "Central Nemuro";
  case 167: return "Southern Nemuro";
  case 180: return "Hokkaido southwest offshore";
  case 181: return "West off Hokkaido";
  case 182: return "Ishikari Bay";
  case 183: return "West off Hokkaido";
  case 184: return "Soya Straits";
  case 186: return "Near Kunashiri Island";
  case 187: return "near Etorofu Island";
  case 188: return "off the east coast of Hokkaido";
  case 189: return "Southeast off Nemuro Peninsula";
  case 190: return "off Kushiro";
  case 191: return "off Tokachi";
  case 192: return "Oki Urakawa";
  case 193: return "off Tomakomai";
  case 194: return "Uchiura Bay";
  case 195: return "East off Soya";
  case 196: return "off Abashiri";
  case 197: return "Southeast off Etorofu Island";
  case 200: return "Northern Tsugaru, Aomori Prefecture";
  case 201: return "Southern Tsugaru, Aomori Prefecture";
  case 202: return "Sanpachi Kamikita region, Aomori Prefecture";
  case 203: return "Shimokita, Aomori Prefecture";
  case 210: return "North Coast of Iwate Prefecture";
  case 211: return "South coast of Iwate prefecture";
  case 212: return "Northern inland Iwate prefecture";
  case 213: return "Inland Southern Iwate Prefecture";
  case 220: return "Northern Miyagi Prefecture";
  case 221: return "Southern Miyagi Prefecture";
  case 222: return "Central Miyagi Prefecture";
  case 230: return "Northern coast of Akita Prefecture";
  case 231: return "Southern coast of Akita Prefecture";
  case 232: return "Northern inland Akita";
  case 233: return "Southern inland Akita prefecture";
  case 240: return "Shonai region, Yamagata Prefecture";
  case 241: return "Mogami district, Yamagata prefecture";
  case 242: return "Yamagata prefecture village area";
  case 243: return "Okitama region, Yamagata Prefecture";
  case 250: return "Nakadori, Fukushima Prefecture";
  case 251: return "Hamadori, Fukushima Prefecture";
  case 252: return "Aizu, Fukushima Prefecture";
  case 280: return "Tsugaru Strait";
  case 281: return "Off Yamagata";
  case 282: return "Off Akita";
  case 283: return "Aomori west coast";
  case 284: return "Mutsu Bay";
  case 285: return "East off Aomori Prefecture";
  case 286: return "off Iwate Prefecture";
  case 287: return "Oki Miyagi Prefecture";
  case 288: return "Off Sanriku";
  case 289: return "Fukushima offshore";
  case 300: return "Northern Ibaraki Prefecture";
  case 301: return "Southern Ibaraki Prefecture";
  case 309: return "off the southeast of Chiba Prefecture";
  case 310: return "Northern Tochigi Prefecture";
  case 311: return "Southern Tochigi Prefecture";
  case 320: return "Northern Gunma Prefecture";
  case 321: return "Southern Gunma Prefecture";
  case 330: return "Northern Saitama";
  case 331: return "Southern Saitama";
  case 332: return "Chichibu, Saitama";
  case 340: return "Northeast Chiba";
  case 341: return "Northwest Chiba";
  case 342: return "Southern Chiba Prefecture";
  case 349: return "off the south of the Boso Peninsula";
  case 350: return "23 wards of Tokyo";
  case 351: return "East Tama, Tokyo";
  case 352: return "West Tama, Tokyo";
  case 360: return "East Kanagawa";
  case 361: return "Western Kanagawa";
  case 370: return "Joetsu Region, Niigata Prefecture";
  case 371: return "Niigata prefecture Chuetsu region";
  case 372: return "Niigata Prefecture Kaetsu Region";
  case 378: return "Off Shimoetsu, Niigata Prefecture";
  case 379: return "Jochuetsu Offing, Niigata Prefecture";
  case 380: return "Eastern Toyama";
  case 381: return "Western Toyama Prefecture";
  case 390: return "Ishikawa prefecture Noto region";
  case 391: return "Kaga region, Ishikawa prefecture";
  case 400: return "Reihoku, Fukui Prefecture";
  case 401: return "Reinan, Fukui Prefecture";
  case 411: return "Central/Western Yamanashi Prefecture";
  case 412: return "Eastern Yamanashi / Fuji Five Lakes";
  case 420: return "Northern Nagano Prefecture";
  case 421: return "Central Nagano";
  case 422: return "Southern Nagano Prefecture";
  case 430: return "Hida region, Gifu Prefecture";
  case 431: return "Eastern Mino, Gifu Prefecture";
  case 432: return "midwest Mino, Gifu Prefecture";
  case 440: return "Izu region, Shizuoka prefecture";
  case 441: return "East Shizuoka";
  case 442: return "Central Shizuoka";
  case 443: return "Western Shizuoka";
  case 450: return "East Aichi Prefecture";
  case 451: return "Western Aichi Prefecture";
  case 460: return "Northern Mie Prefecture";
  case 461: return "Central Mie Prefecture";
  case 462: return "Southern Mie Prefecture";
  case 469: return "off the southeast of Mie Prefecture";
  case 471: return "off Ibaraki";
  case 472: return "Kanto Tohooki";
  case 473: return "off the east coast of Chiba Prefecture";
  case 475: return "East off Hachijojima";
  case 476: return "Sea near Hachijojima";
  case 477: return "Tokyo Bay";
  case 478: return "Sagami Bay";
  case 480: return "Sea near Izu Oshima";
  case 481: return "East off Izu Peninsula";
  case 482: return "Sea near Miyakejima";
  case 483: return "Sea near Niijima and Kozushima";
  case 485: return "Suruga Bay";
  case 486: return "South of Suruga Bay";
  case 487: return "Enshunada";
  case 489: return "Mikawa Bay";
  case 490: return "Isewan";
  case 492: return "Wakasa Bay";
  case 493: return "off Fukui Prefecture";
  case 494: return "West Off Ishikawa Prefecture";
  case 495: return "Off Noto Peninsula";
  case 497: return "Toyama Bay";
  case 498: return "Near Sado";
  case 499: return "off the south of Tokaido";
  case 500: return "Northern Shiga Prefecture";
  case 501: return "Southern Shiga Prefecture";
  case 510: return "Northern Kyoto Prefecture";
  case 511: return "South Kyoto";
  case 520: return "Northern Osaka Prefecture";
  case 521: return "South Osaka Prefecture";
  case 530: return "Northern Hyogo Prefecture";
  case 531: return "Southeastern Hyogo Prefecture";
  case 532: return "Southwest Hyogo Prefecture";
  case 540: return "Nara Prefecture";
  case 550: return "Northern Wakayama Prefecture";
  case 551: return "South Wakayama Prefecture";
  case 560: return "Eastern Tottori Prefecture";
  case 562: return "Central Tottori";
  case 563: return "Western Tottori Prefecture";
  case 570: return "East Shimane Prefecture";
  case 571: return "Western Shimane Prefecture";
  case 580: return "Northern Okayama Prefecture";
  case 581: return "Southern Okayama Prefecture";
  case 590: return "Northern Hiroshima Prefecture";
  case 591: return "Southeastern Hiroshima Prefecture";
  case 592: return "Southwest Hiroshima Prefecture";
  case 600: return "Northern Tokushima";
  case 601: return "Southern Tokushima Prefecture";
  case 610: return "East Kagawa Prefecture";
  case 611: return "Western Kagawa Prefecture";
  case 620: return "Toyo, Ehime Prefecture";
  case 621: return "Ehime prefecture Chuyo";
  case 622: return "Nanyo, Ehime Prefecture";
  case 630: return "East Kochi Prefecture";
  case 631: return "Central Kochi Prefecture";
  case 632: return "Western Kochi Prefecture";
  case 673: return "Tosa Bay";
  case 674: return "Kii Channel";
  case 675: return "Osaka Bay";
  case 676: return "Harimanada";
  case 677: return "Central Seto Inland Sea";
  case 678: return "Akinada";
  case 679: return "Suonada";
  case 680: return "Iyonada";
  case 681: return "Bungo Channel";
  case 682: return "Northwest off Yamaguchi";
  case 683: return "Off Shimane";
  case 684: return "offshore Tottori";
  case 685: return "Sea near Oki Islands";
  case 686: return "Northern off Hyogo Prefecture";
  case 687: return "Off Kyoto";
  case 688: return "near Awaji Island";
  case 689: return "Southern Wakayama Prefecture";
  case 700: return "Northern Yamaguchi Prefecture";
  case 702: return "Western Yamaguchi";
  case 703: return "Eastern Yamaguchi";
  case 704: return "Central Yamaguchi";
  case 710: return "Fukuoka region, Fukuoka prefecture";
  case 711: return "Kitakyushu, Fukuoka";
  case 712: return "Chikuho region, Fukuoka Prefecture";
  case 713: return "Chikugo, Fukuoka";
  case 720: return "Northern Saga Prefecture";
  case 721: return "Southern Saga Prefecture";
  case 730: return "Northern Nagasaki Prefecture";
  case 731: return "Southwest Nagasaki Prefecture";
  case 732: return "Shimabara Peninsula, Nagasaki Prefecture";
  case 740: return "Aso region, Kumamoto Prefecture";
  case 741: return "Kumamoto region, Kumamoto prefecture";
  case 742: return "Kuma region, Kumamoto prefecture";
  case 743: return "Kumamoto prefecture Amakusa/Ashikita region";
  case 750: return "Northern Oita Prefecture";
  case 751: return "Central Oita";
  case 752: return "Southern Oita Prefecture";
  case 753: return "Western Oita Prefecture";
  case 760: return "Northern plains of Miyazaki Prefecture";
  case 761: return "Along the mountains in northern Miyazaki Prefecture";
  case 762: return "Southern plains of Miyazaki Prefecture";
  case 763: return "Along the mountains in southern Miyazaki Prefecture";
  case 770: return "Satsuma region, Kagoshima Prefecture";
  case 771: return "Osumi region, Kagoshima prefecture";
  case 783: return "Sea near the Goto Islands";
  case 784: return "Amakusa Nada";
  case 785: return "Ariake Sea";
  case 786: return "Tachibanawan";
  case 787: return "Kagoshima Bay";
  case 790: return "Sea near Tanegashima";
  case 791: return "Hyuganada";
  case 793: return "Sea near Amami Oshima";
  case 795: return "Sea near Iki and Tsushima";
  case 796: return "North West Off Fukuoka";
  case 797: return "West off Satsuma Peninsula";
  case 798: return "Sea near the Tokara Islands";
  case 799: return "Northwest off Amami Oshima";
  case 820: return "East off Osumi Peninsula";
  case 821: return "Southeast off Kyushu";
  case 822: return "Southeast off Tanegashima";
  case 823: return "Northeast of Amami Oshima";
  case 850: return "Sea near Okinawa main island";
  case 851: return "Sea near Minamidaito Island";
  case 852: return "south off the main island of Okinawa";
  case 853: return "Sea near Miyakojima";
  case 854: return "Sea near Ishigaki Island";
  case 855: return "Southern offshore of Ishigaki Island";
  case 856: return "near Iriomote Island";
  case 857: return "Sea near Yonaguni Island";
  case 858: return "Northwest off the main island of Okinawa";
  case 859: return "Northwest off Miyako Island";
  case 860: return "Northwest offshore of Ishigaki Island";
  case 900: return "Near Taiwan";
  case 901: return "East China Sea";
  case 902: return "off Shikoku";
  case 903: return "Sea near Torishima";
  case 904: return "East off Torishima";
  case 905: return "Southern Sea of Okhotsk";
  case 906: return "West off Sakhalin";
  case 907: return "Northern Japan Sea";
  case 908: return "Central Sea of Japan";
  case 909: return "Western Sea of Japan";
  case 911: return "Sea near Chichijima";
  case 912: return "Kilil Islands";
  case 913: return "Southeast off the Kurile Islands";
  case 914: return "off the southeast of Hokkaido";
  case 915: return "Tohoku offshore";
  case 916: return "off the west coast of the Ogasawara Islands";
  case 917: return "Sea near Iwo Jima";
  case 918: return "offshore east of the Ogasawara Islands";
  case 919: return "South of Nankaido";
  case 920: return "off the east of the Satsunan Islands";
  case 921: return "off the southern coast of Honshu";
  case 922: return "near Southern Sakhalin";
  case 930: return "Northwest Pacific";
  case 932: return "Mariana Islands";
  case 933: return "Yellow Sea";
  case 934: return "South Korean Peninsula";
  case 935: return "Northern Korean Peninsula";
  case 936: return "Northeast China";
  case 937: return "near Vladivostok";
  case 938: return "Southern Siberia";
  case 939: return "Sea near Sakhalin";
  case 940: return "Aleutian Islands";
  case 941: return "near Kamchatka Peninsula";
  case 942: return "NA West";
  case 943: return "Central North America";
  case 944: return "East North America";
  case 945: return "Central America";
  case 946: return "South America West";
  case 947: return "Central South America";
  case 948: return "East South America";
  case 949: return "Northeast Pacific";
  case 950: return "South Pacific";
  case 951: return "Near the Indochina Peninsula";
  case 952: return "near Philippines";
  case 953: return "Near Indonesia";
  case 954: return "Near Guam";
  case 955: return "near new gear";
  case 956: return "Near New Zealand";
  case 957: return "near Australia";
  case 958: return "Near Siberia";
  case 959: return "West Russia";
  case 960: return "Central Russia";
  case 961: return "Russia East";
  case 962: return "Central Asia";
  case 963: return "West China";
  case 964: return "Central China";
  case 965: return "East China";
  case 966: return "Near India";
  case 967: return "Indian Ocean";
  case 968: return "Middle East";
  case 969: return "West Europe";
  case 970: return "Central Europe";
  case 971: return "East Europe";
  case 972: return "Mediterranean";
  case 973: return "West Africa";
  case 974: return "Central Africa";
  case 975: return "East Africa";
  case 976: return "North Atlantic";
  case 977: return "South Atlantic";
  case 978: return "near North Pole";
  case 979: return "near Antarctica";
  case 999: return "far";
  case 1000: return "other epicenter name";
  default:
    snprintf(_undefMessage, sizeof(_undefMessage),
            "Epicenter name (code number: %d)", code);
    return _undefMessage;
  }
}
#endif // defined(QZQSM_ENABLE_DC1) || defined(QZQSM_ENABLE_DC2)

#ifdef QZQSM_ENABLE_DC1

// Seismic Intensity
const char* QZQSM::dc1si2str(int code)
{
  switch (code) {
  case 1: return "seismic intensity 0";
  case 2: return "seismic intensity 1";
  case 3: return "seismic intensity 2";
  case 4: return "seismic intensity 3";
  case 5: return "seismic intensity 4";
  case 6: return "seismic intensity 5 lower";
  case 7: return "Seismic intensity 5 Upper";
  case 8: return "seismic intensity 6 lower";
  case 9: return "seismic intensity 6 upper";
  case 10: return "seismic intensity 7";
  case 11: return "more than or equal to";
  case 14: return "none";
  case 15: return "unknown";
  default: return "";
  }
}

// Forecast Region Earthquake Early Warning (Region)
const char* QZQSM::dc1pl2str(int code)
{
   switch (code) {
   case 1: return "Central Hokkaido";
   case 2: return "Hokkaido Donan";
   case 3: return "Hokkaido Dohoku";
   case 4: return "East Hokkaido";
   case 5: return "Aomori";
   case 6: return "Iwate";
   case 7: return "Miyagi";
   case 8: return "Akita";
   case 9: return "Yamagata";
   case 10: return "Fukushima";
   case 11: return "Ibaraki";
   case 12: return "Tochigi";
   case 13: return "Gunma";
   case 14: return "Saitama";
   case 15: return "Chiba";
   case 16: return "Tokyo";
   case 17: return "Izu Islands";
   case 18: return "Ogasawara";
   case 19: return "Kanagawa";
   case 20: return "Niigata";
   case 21: return "Toyama";
   case 22: return "Ishikawa";
   case 23: return "Fukui";
   case 24: return "Yamanashi";
   case 25: return "Nagano";
   case 26: return "Gifu";
   case 27: return "Shizuoka";
   case 28: return "Aichi";
   case 29: return "Mie";
   case 30: return "Shiga";
   case 31: return "Kyoto";
   case 32: return "Osaka";
   case 33: return "Hyogo";
   case 34: return "Nara";
   case 35: return "Wakayama";
   case 36: return "Tottori";
   case 37: return "Shimane";
   case 38: return "Okayama";
   case 39: return "Hiroshima";
   case 40: return "Yamaguchi";
   case 41: return "Tokushima";
   case 42: return "Kagawa";
   case 43: return "Ehime";
   case 44: return "Kochi";
   case 45: return "Fukuoka";
   case 46: return "Saga";
   case 47: return "Nagasaki";
   case 48: return "Kumamoto";
   case 49: return "Oita";
   case 50: return "Miyazaki";
   case 51: return "Kagoshima";
   case 52: return "Amami (Archipelago)";
   case 53: return "Okinawa main island";
   case 54: return "Daito Island";
   case 55: return "Miyakojima";
   case 56: return "Yaeyama";
   case 57: return "Hokkaido";
   case 58: return "Tohoku";
   case 59: return "Kanto";
   case 60: return "Izu Islands";
   case 61: return "Ogasawara";
   case 62: return "Hokuriku";
   case 63: return "Koshin";
   case 64: return "Tokai";
   case 65: return "Kinki";
   case 66: return "China";
   case 67: return "Shikoku";
   case 68: return "Kyushu";
   case 69: return "Amami (Archipelago)";
   case 70: return "Okinawa";
   case 80: return "Other Prefectural Forecast Areas and Local Forecast Areas";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "prefectural forecast area and local forecast area (point: %d)", code);
     return _undefMessage;
   }
}

int QZQSM::filter_dc1()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc1()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC1_REPORT, it2str(_Header.It));
  int num;
  for (num = 0; num < 3; num++) {
    if (_u.Dc1.Co[num] != 0) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC1_REPORT2, dc1co2str(_u.Dc1.Co[num]));
    }
  }
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC1_REPORT3, _jstAtMo, _jstAtD, _jstAtH, _jstAtMi,
                   dc1ep2str(_u.Dc1.Ep),
                   _u.Dc1.OtD, _u.Dc1.OtH, _u.Dc1.OtM,
                   dc1de2str(_u.Dc1.De),
                   dc1ma2str(_u.Dc1.Ma),
                   dc1si2str(_u.Dc1.Ll), dc1si2str(_u.Dc1.Ul));
  int b;
  for (b = 0; b < 32; b++) {
    if (_u.Dc1.Pl[0] & (1 << (31 - b))) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC1_REPORT4, dc1pl2str(b + 1));
    }
  }
  for (b = 0; b < 32; b++) {
    if (_u.Dc1.Pl[1] & (1 << (31 - b))) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC1_REPORT4, dc1pl2str(b + 32 + 1));
    }
  }
  for (b = 0; b < 16; b++) {
    if (_u.Dc1.Pl[2] & (1 << (15 - b))) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC1_REPORT4, dc1pl2str(b + 64 + 1));
    }
  }
}

void QZQSM::decode_dc1()
{
  int num;
  for (num = 0; num < 3; num++) {
    _u.Dc1.Co[num] = get_val(53 + (9 * num), 9);
  }
  _u.Dc1.OtD = get_val(80, 5);
  _u.Dc1.OtH = get_val(85, 5);
  _u.Dc1.OtM = get_val(90, 6);
  _u.Dc1.De  = get_val(96, 9);
  _u.Dc1.Ma  = get_val(105, 7);
  _u.Dc1.Ep  = get_val(112, 10);
  _u.Dc1.Ll  = get_val(122, 4);
  _u.Dc1.Ul  = get_val(126, 4);
  _u.Dc1.Pl[0] = get_val(130, 32);
  _u.Dc1.Pl[1] = get_val(162, 32);
  _u.Dc1.Pl[2] = get_val(194, 16);

  utc2jst(_Header.AtMo, _u.Dc1.OtD, _u.Dc1.OtH, _u.Dc1.OtM);
}
#endif // QZQSM_ENABLE_DC1

//===============================================================
// Disaster Category Code 2
// JMA-DC Report (Hypocenter)

#ifdef QZQSM_ENABLE_DC2

#define DC2_REPORT \
   "Disaster alert (earthquake) (%s)\n" \
   "On %d days %d hours %d minutes there was an earthquake.\n"

#define DC2_REPORT2 "%s\n"

#define DC2_REPORT3 \
   "\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n" \
   "Epicenter name: %s\n" \
   "Latitude/Longitude: %s%d degrees %d minutes %d seconds %s%d degrees %d minutes %d seconds\n" \
   "Depth (km): %s\n" \
   "magnitude: %s\n"

int QZQSM::filter_dc2()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc2()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC2_REPORT, it2str(_Header.It), _u.Dc2.OtD, _u.Dc2.OtH, _u.Dc2.OtM);
  int num;
  for (num = 0; num < 3; num++) {
    if (_u.Dc2.Co[num] != 0) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC2_REPORT2, dc1co2str(_u.Dc2.Co[num]));
    }
  }
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC2_REPORT3, _jstAtMo, _jstAtD, _jstAtH, _jstAtMi,
                   dc1ep2str(_u.Dc2.Ep),
                   _u.Dc2.LatNs ? "South" : "North", _u.Dc2.LatD, _u.Dc2.LatM, _u.Dc2.LatS,
                    _u.Dc2.LonEw ? "West longitude" : "East longitude", _u.Dc2.LonD, _u.Dc2.LonM, _u.Dc2.LonS,
                   dc1de2str(_u.Dc2.De),
                   dc1ma2str(_u.Dc2.Ma));
}

void QZQSM::decode_dc2()
{
  _u.Dc2.OtD = get_val(80, 5);
  _u.Dc2.OtH = get_val(85, 5);
  _u.Dc2.OtM = get_val(90, 6);
  int num;
  for (num = 0; num < 3; num++) {
    _u.Dc2.Co[num] = get_val(53 + (9 * num), 9);
  }
  _u.Dc2.De = get_val(96, 9);
  _u.Dc2.Ma = get_val(105, 7);
  _u.Dc2.Ep = get_val(112, 10);
  _u.Dc2.LatNs = get_val(122, 1);
  _u.Dc2.LatD = get_val(123, 7);
  _u.Dc2.LatM = get_val(130, 6);
  _u.Dc2.LatS = get_val(136, 6);
  _u.Dc2.LonEw = get_val(142, 1);
  _u.Dc2.LonD = get_val(143, 8);
  _u.Dc2.LonM = get_val(151, 6);
  _u.Dc2.LonS = get_val(157, 6);

  utc2jst(_Header.AtMo, _u.Dc2.OtD, _u.Dc2.OtH, _u.Dc2.OtM);
}
#endif // QZQSM_ENABLE_DC2

//===============================================================
// Disaster Category Code 3
// JMA-DC Report (Seismic Intensity)

#ifdef QZQSM_ENABLE_DC3

#define DC3_REPORT \
   "Disaster report (seismic intensity) (%s)\n" \
   "On %d days %d hours %d minutes, I felt a strong tremor from an earthquake.\n" \
   "\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n"

#define DC3_REPORT2 "%s: %s\n"

// Seismic Intensity (Region)
const char* QZQSM::dc3es2str(int code)
{
   switch (code) {
   case 1: return "less than seismic intensity 4";
   case 2: return "seismic intensity 4";
   case 3: return "seismic intensity 5 lower";
   case 4: return "Seismic intensity 5 Upper";
   case 5: return "seismic intensity 6 lower";
   case 6: return "seismic intensity 6 upper";
   case 7: return "seismic intensity 7";
   default: return "";
   }
}

// Prefecture (Region)
const char* QZQSM::dc3pl2str(int code)
{
   switch (code) {
   case 1: return "Hokkaido";
   case 2: return "Aomori Prefecture";
   case 3: return "Iwate Prefecture";
   case 4: return "Miyagi Prefecture";
   case 5: return "Akita Prefecture";
   case 6: return "Yamagata Prefecture";
   case 7: return "Fukushima Prefecture";
   case 8: return "Ibaraki Prefecture";
   case 9: return "Tochigi Prefecture";
   case 10: return "Gunma Prefecture";
   case 11: return "Saitama Prefecture";
   case 12: return "Chiba Prefecture";
   case 13: return "Tokyo";
   case 14: return "Kanagawa Prefecture";
   case 15: return "Niigata Prefecture";
   case 16: return "Toyama Prefecture";
   case 17: return "Ishikawa Prefecture";
   case 18: return "Fukui Prefecture";
   case 19: return "Yamanashi Prefecture";
   case 20: return "Nagano Prefecture";
   case 21: return "Gifu Prefecture";
   case 22: return "Shizuoka Prefecture";
   case 23: return "Aichi Prefecture";
   case 24: return "Mie Prefecture";
   case 25: return "Shiga Prefecture";
   case 26: return "Kyoto";
   case 27: return "Osaka";
   case 28: return "Hyogo Prefecture";
   case 29: return "Nara Prefecture";
   case 30: return "Wakayama Prefecture";
   case 31: return "Tottori Prefecture";
   case 32: return "Shimane Prefecture";
   case 33: return "Okayama Prefecture";
   case 34: return "Hiroshima Prefecture";
   case 35: return "Yamaguchi Prefecture";
   case 36: return "Tokushima Prefecture";
   case 37: return "Kagawa Prefecture";
   case 38: return "Ehime Prefecture";
   case 39: return "Kochi Prefecture";
   case 40: return "Fukuoka Prefecture";
   case 41: return "Saga Prefecture";
   case 42: return "Nagasaki Prefecture";
   case 43: return "Kumamoto Prefecture";
   case 44: return "Oita Prefecture";
   case 45: return "Miyazaki Prefecture";
   case 46: return "Kagoshima Prefecture";
   case 47: return "Okinawa Prefecture";
   default: return "";
   }
}

int QZQSM::filter_dc3()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc3()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC3_REPORT, it2str(_Header.It), _u.Dc3.OtD, _u.Dc3.OtH, _u.Dc3.OtM,
                   _jstAtMo, _jstAtD, _jstAtH, _jstAtMi);
  int num;
  for (num = 0; num < 16; num++) {
    if ((_u.Dc3.site[num].Es != 0) && (_u.Dc3.site[num].Pl != 0)) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC3_REPORT2, dc3es2str(_u.Dc3.site[num].Es), dc3pl2str(_u.Dc3.site[num].Pl));
    }
  }
}

void QZQSM::decode_dc3()
{
  _u.Dc3.OtD = get_val(53, 5);
  _u.Dc3.OtH = get_val(58, 5);
  _u.Dc3.OtM = get_val(63, 6);
  int num;
  for (num = 0; num < 16; num++) {
    _u.Dc3.site[num].Es = get_val(69 + (9 * num), 3);
    _u.Dc3.site[num].Pl = get_val(72 + (9 * num), 6);
  }
  utc2jst(_Header.AtMo, _u.Dc3.OtD, _u.Dc3.OtH, _u.Dc3.OtM);
}
#endif // QZQSM_ENABLE_DC3

//===============================================================
// Disaster Category Code 4
// JMA-DC Report (Nankai Trough Earthquake)

#ifdef QZQSM_ENABLE_DC4

#define DC4_REPORT \
   "Disaster report (Nankai Trough earthquake)(%s)(%d/%d)\n\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n"

#define DC4_REPORT2 \
  "%s\n"

int QZQSM::filter_dc4()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc4()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC4_REPORT, it2str(_Header.It), _u.Dc4.Pn, _u.Dc4.Pm, _jstAtMo, _jstAtD, _jstAtH, _jstAtMi);
  int num;
  for (num = 0; num < 18; num++) {
    if (_u.Dc4.Te[num] == 0) {
      break;
    }
  }
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC4_REPORT2, _u.Dc4.Te);
}

void QZQSM::decode_dc4()
{
  _u.Dc4.Pn = get_val(201, 6);
  _u.Dc4.Pm = get_val(207, 6);
  int num;
  for (num = 0; num < 18; num++) {
    _u.Dc4.Te[num] = get_val(57 + (8 * num), 8);
  }
}
#endif // QZQSM_ENABLE_DC4

//===============================================================
// Disaster Category Code 5
// JMA-DC Report (Tsunami)

#ifdef QZQSM_ENABLE_DC5

#define DC5_REPORT \
   "Disaster Report (Tsunami)(%s)\n" \
   "Announced %s.\n"

#define DC5_REPORT2 \
   "%s\n"

#define DC5_REPORT3 \
   "\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n"

#define DC5_REPORT4 \
   "Estimated time of arrival of tsunami: %s\n" \
   "Tsunami height: %s\n" \
   "%s\n\n"

// Warning Code
const char* QZQSM::dc5dw2str(int code)
{
   switch (code) {
   case 1: return "no tsunami";
   case 2: return "alarm off";
   case 3: return "Tsunami Warning";
   case 4: return "Major Tsunami Warning";
   case 5: return "Major Tsunami Warning: Announcement";
   case 15: return "Other alerts";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "alarm (code number: %d)", code);
     return _undefMessage;
   }
}

// Tsunami Arrival Time
const char* QZQSM::dc5ta2str(int h, int m)
{
   if ((h == 31) && (m == 63)) {
     return "reach";
   }
   snprintf(_undefMessage, sizeof(_undefMessage),
            "%d hours %d minutes", h, m);
   return _undefMessage;
}

// Tsunami Height
const char* QZQSM::dc5th2str(int code)
{
   switch (code) {
   case 1: return "Less than 0.2m";
   case 2: return "1m";
   case 3: return "3m";
   case 4: return "5m";
   case 5: return "10m";
   case 6: return "more than 10m";
   case 14: return "unknown";
   case 15: return "other tsunami heights";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Tsunami height (code number: %d)", code);
     return _undefMessage;
   }
}

// Tsunami Forecast Region
const char* QZQSM::dc5pl2str(int code)
{
   switch (code) {
   case 11000: return "Soya region";
   case 100: return "Eastern Pacific Coast of Hokkaido";
   case 101: return "Central Pacific Coast of Hokkaido";
   case 102: return "Hokkaido Pacific West";
   case 110: return "North coast of Hokkaido, Japan";
   case 111: return "Southern coast of Hokkaido, Japan";
   case 120: return "Sea of Okhotsk coast";
   case 191: return "Hokkaido Pacific Coast";
   case 192: return "Hokkaido Sea of Japan coast";
   case 193: return "Sea of Okhotsk coast";
   case 200: return "Coast of the Sea of Japan in Aomori Prefecture";
   case 201: return "Pacific Coast of Aomori Prefecture";
   case 202: return "Mutsu Bay";
   case 210: return "Iwate Prefecture";
   case 220: return "Miyagi Prefecture";
   case 230: return "Akita Prefecture";
   case 240: return "Yamagata Prefecture";
   case 250: return "Fukushima Prefecture";
   case 281: return "Aomori Prefecture";
   case 291: return "Tohoku Pacific Coast";
   case 292: return "Tohoku region Sea of Japan coast";
   case 300: return "Ibaraki Prefecture";
   case 310: return "Kujuri, Sotobo, Chiba Prefecture";
   case 311: return "Uchibo, Chiba Prefecture";
   case 312: return "Tokyo Bay Inner Bay";
   case 320: return "Izu Islands";
   case 321: return "Ogasawara Islands";
   case 330: return "Sagami Bay/Miura Peninsula";
   case 340: return "Kaminakageetsu, Niigata Prefecture";
   case 341: return "Sado";
   case 350: return "Toyama Prefecture";
   case 360: return "Noto, Ishikawa Prefecture";
   case 361: return "Kaga, Ishikawa Prefecture";
   case 370: return "Fukui Prefecture";
   case 380: return "Shizuoka Prefecture";
   case 390: return "Aichi Prefecture Sotome";
   case 391: return "Ise/Mikawa Bay";
   case 400: return "Southern Mie Prefecture";
   case 481: return "Chiba Prefecture";
   case 482: return "Kanagawa Prefecture";
   case 483: return "Niigata Prefecture";
   case 484: return "Ishikawa Prefecture";
   case 485: return "Aichi Prefecture";
   case 486: return "Mie Prefecture";
   case 491: return "Kanto region";
   case 492: return "Izu/Ogasawara Islands";
   case 493: return "Hokuriku";
   case 494: return "Tokai region";
   case 500: return "Kyoto";
   case 510: return "Osaka";
   case 520: return "Northern Hyogo Prefecture";
   case 521: return "Seto Inland Sea Coast, Hyogo Prefecture";
   case 522: return "Southern Awaji Island";
   case 530: return "Wakayama Prefecture";
   case 540: return "Tottori Prefecture";
   case 550: return "Izumo/Iwami, Shimane Prefecture";
   case 551: return "Oki";
   case 560: return "Okayama Prefecture";
   case 570: return "Hiroshima Prefecture";
   case 580: return "Tokushima Prefecture";
   case 590: return "Kagawa Prefecture";
   case 600: return "Uwakai Coast, Ehime Prefecture";
   case 601: return "Ehime Prefecture Seto Inland Sea Coast";
   case 610: return "Kochi Prefecture";
   case 681: return "Hyogo Prefecture";
   case 682: return "Shimane Prefecture";
   case 683: return "Ehime Prefecture";
   case 691: return "Kinki Shikoku Pacific Coast";
   case 692: return "Kinki Chugoku Sea of Japan coast";
   case 693: return "Seto Inland Sea Coast";
   case 700: return "Japan Sea Coast in Yamaguchi Prefecture";
   case 701: return "Yamaguchi Prefecture Seto Inland Sea Coast";
   case 710: return "Fukuoka Seto Inland Sea Coast";
   case 711: return "Fukuoka Prefecture Sea of Japan Coast";
   case 712: return "Ariake/Yatsushiroumi";
   case 720: return "Northern Saga Prefecture";
   case 730: return "West Nagasaki Prefecture";
   case 731: return "Iki/Tsushima";
   case 740: return "Amakusa Sea coast, Kumamoto Prefecture";
   case 750: return "Oita Prefecture Seto Inland Sea Coast";
   case 751: return "Bungo Channel Coast, Oita Prefecture";
   case 760: return "Miyazaki Prefecture";
   case 770: return "East Kagoshima Prefecture";
   case 771: return "Tanegashima/Yakushima region";
   case 772: return "Amami Islands/Tokara Islands";
   case 773: return "Western Kagoshima Prefecture";
   case 781: return "Yamaguchi Prefecture";
   case 782: return "Fukuoka Prefecture";
   case 783: return "Saga Prefecture";
   case 784: return "Nagasaki Prefecture";
   case 785: return "Kumamoto Prefecture";
   case 786: return "Oita Prefecture";
   case 787: return "Kagoshima Prefecture";
   case 791: return "Eastern Kyushu";
   case 792: return "Western Kyushu";
   case 793: return "Satsunan Islands";
   case 800: return "Okinawa Main Island Region";
   case 801: return "Daito Island Region";
   case 802: return "Miyakojima/Yaeyama region";
   case 891: return "Okinawa region";
   case 990: return "GPS wave gauge";
   case 1000: return "other tsunami forecast areas";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Tsunami forecast area (code number: %d)", code);
     return _undefMessage;
   }
}

int QZQSM::filter_dc5()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc5()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC5_REPORT, it2str(_Header.It), dc5dw2str(_u.Dc5.Dw));
  int num;
  for (num = 0; num < 3; num++) {
    if (_u.Dc5.Co[num] != 0) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC5_REPORT2, dc1co2str(_u.Dc5.Co[num]));
    }
  }
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC5_REPORT3, _jstAtMo, _jstAtD, _jstAtH, _jstAtMi);
  for (num = 0; num < 5; num++) {
    if (_u.Dc5.site[num].Pl != 0) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC5_REPORT4, dc5ta2str(_u.Dc5.site[num].TaH, _u.Dc5.site[num].TaM),
                       dc5th2str(_u.Dc5.site[num].Th), dc5pl2str(_u.Dc5.site[num].Pl));
    }
  }
}

void QZQSM::decode_dc5()
{
  _u.Dc5.Dw = get_val(80, 4);
  int num;
  for (num = 0; num < 3; num++) {
    _u.Dc5.Co[num] = get_val(53 + (9 * num), 9);
  }
  for (num = 0; num < 5; num++) {
    _u.Dc5.site[num].TaD = get_val(84 + (26 * num), 1);
    _u.Dc5.site[num].TaH = get_val(85 + (26 * num), 5);
    _u.Dc5.site[num].TaM = get_val(90 + (26 * num), 6);
    _u.Dc5.site[num].Th  = get_val(96 + (26 * num), 4);
    _u.Dc5.site[num].Pl  = get_val(100 + (26 * num), 10);
    if ((_u.Dc5.site[num].TaH != 31) && (_u.Dc5.site[num].TaM != 63)) {
      utc2jst(_Header.AtMo, _Header.AtD, _u.Dc5.site[num].TaH, _u.Dc5.site[num].TaM);
    }
  }
}
#endif // QZQSM_ENABLE_DC5

//===============================================================
// Disaster Category Code 6
// JMA-DC Report (Northwest Pacific Tsunami)

#ifdef QZQSM_ENABLE_DC6

#define DC6_REPORT \
   "Disaster Alert (Northeast Pacific Tsunami)(%s)\n" \
   "%s\n\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n"

#define DC6_REPORT2 \
   "Estimated time of arrival of tsunami: %s\n" \
   "Tsunami height: %s\n" \
   "%s\n\n"

// Tsunamigenic Potential
const char* QZQSM::dc6tp2str(int code)
{
   switch (code) {
   case 0: return "THERE IS NO POSSIBILITY OF A TSUNAMI";
   case 1: return "THERE IS A POSSIBILITY OF A DESTRUCTIVE OCEAN-WIDE TSUNAMI";
   case 2: return "THERE IS A POSSIBILITY OF A DESTRUCTIVE REGIONAL TSUNAMI";
   case 3: return "THERE IS A POSSIBILITY OF A DESTRUCTIVE LOCAL TSUNAMI NEAR THE EPICENTER";
   case 4: return "THERE IS A VERY SMALL POSSIBILITY OF A DESTRUCTIVE LOCAL TSUNAMI";
   case 7: return "Possibility of occurrence of other tsunamis";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Possibility of tsunami occurrence (code number: %d)", code);
     return _undefMessage;
   }
}

// Tsunami Arrival Time
const char* QZQSM::dc6ta2str(int h, int m)
{
   if ((h == 31) && (m == 63)) {
     return "reached or unknown";
   }
   snprintf(_undefMessage, sizeof(_undefMessage),
            "%d hours %d minutes", h, m);
   return _undefMessage;
}

// Tsunami Height
const char* QZQSM::dc6th2str(int code)
{
   switch (code) {
   case 1: return "0.3m～1m";
   case 2: return "1m～3m";
   case 3: return "3m～5m";
   case 4: return "5m～10m";
   case 508: return "more than 10m";
   case 509: return "huge";
   case 510: return "high";
   case 511: return "unknown";
   default: return "";
   }
}

// Coastal Region
const char* QZQSM::dc6pl2str(int code)
{
  switch (code) {
  case  1: return "Ust-Kamchatsk (Kamchatka Peninsula east coast)";
  case  2: return "Petropavlovsk (Kamchatka Peninsula east coast)";
  case  3: return "Severo Kurilsk (Kuril Islands)";
  case  4: return "Urup Islands (Kuril Islands)";
  case  5: return "Busan (Korean Peninsula south coast)";
  case  6: return "Nohwa (Korean Peninsula south coast)";
  case  7: return "Seogwipo (Korean Peninsula south coast)";
  case  8: return "Fualien (Taiwan east coast)";
  case  9: return "Basco (Philippines east coast)";
  case 10: return "Palanan (Philippines east coast)";
  case 11: return "Legaspi (Philippines east coast)";
  case 12: return "Laoang (Philippines east coast)";
  case 13: return "Madrid (Philippines east coast)";
  case 14: return "Davao (Philippines east coast)";
  case 15: return "Berebere (Irian Jaya north coast)";
  case 16: return "Patani (Irian Jaya north coast)";
  case 17: return "Sorong (Irian Jaya north coast)";
  case 18: return "Manokwari (Irian Jaya north coast)";
  case 19: return "Warsa (Irian Jaya north coast)";
  case 20: return "Jayapura (Irian Jaya north coast)";
  case 21: return "Vanimo (Papua New Guinea north coast)";
  case 22: return "Wewak (Papua New Guinea north coast)";
  case 23: return "Madang (Papua New Guinea north coast)";
  case 24: return "Manus Islands (Papua New Guinea north coast)";
  case 25: return "Rabaul (Papua New Guinea north coast)";
  case 26: return "Kavieng (Papua New Guinea north coast)";
  case 27: return "Kimbe (Papua New Guinea north coast)";
  case 28: return "Kieta (Papua New Guinea north coast)";
  case 29: return "Guam (Mariana Islands)";
  case 30: return "Saipan (Mariana Islands)";
  case 31: return "Malakal (Palau Islands)";
  case 32: return "Yap Island (Micronesia)";
  case 33: return "Chuuk Island (Micronesia)";
  case 34: return "Pohnpei Island (Micronesia)";
  case 35: return "Kosrae Island (Micronesia)";
  case 36: return "Eniwetok Island (Marshall Islands)";
  case 37: return "Panggoe (Solomon Islands north coast)";
  case 38: return "Auki (Solomon Islands north coast)";
  case 39: return "Kirakira (Solomon Islands north coast)";
  case 40: return "Munda (Solomon Sea)";
  case 41: return "Honiara (Solomon Sea)";
  case 42: return "Hong Kong (South China Sea north coast)";
  case 43: return "Sanya (South China Sea north coast)";
  case 44: return "Vinh (Tonkin Gulf coast)";
  case 45: return "Qui Nhon (Indochina Peninsula east coast)";
  case 46: return "Bac Lieu (Indochina Peninsula east coast)";
  case 47: return "Prachuap Khiri Khan (Thailand Gulf coast)";
  case 48: return "Sihanoukville (Thailand Gulf coast)";
  case 49: return "Nakhon Si Thammarat (Thailand Gulf coast)";
  case 50: return "Muara (Kalimantan northwest coast)";
  case 51: return "Bintulu (Kalimantan northwest coast)";
  case 52: return "Laoag (Philippines west coast)";
  case 53: return "San Fernando (Philippines west coast)";
  case 54: return "Manila (Philippines west coast)";
  case 55: return "Iloilo (Sulu Sea coast)";
  case 56: return "Puerto Princesa (Sulu Sea coast)";
  case 57: return "Sandakan (Sulu Sea coast)";
  case 58: return "Kuara Terengganu (Malay Peninsula east coast)";
  case 59: return "Singapore (Malay Peninsula east coast)";
  case 60: return "Zamboanga (Celebes Sea coast)";
  case 61: return "Tarakan (Celebes Sea coast)";
  case 62: return "Manado (Celebes Sea coast)";
  case 63: return "Tolitoli (Celebes Sea coast)";
  case 64: return "Singkawang (Natuna Sea coast)";
  case 65: return "Pangkalpinang (Natuna Sea coast)";
  case 99: return "Unknown";
  case 100: return "Other region";
  default:
    snprintf(_undefMessage, sizeof(_undefMessage),
             "Coastal Region(Code:%d)", code);
    return _undefMessage;
  }
}

int QZQSM::filter_dc6()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc6()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC6_REPORT, it2str(_Header.It), dc6tp2str(_u.Dc6.Tp),
                   _jstAtMo, _jstAtD, _jstAtH, _jstAtMi);
  int num;
  for (num = 0; num < 5; num++) {
    if (_u.Dc6.site[num].Pl != 0) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC6_REPORT2, dc6ta2str(_u.Dc6.site[num].TaH, _u.Dc6.site[num].TaM),
                       dc6th2str(_u.Dc6.site[num].Th), dc6pl2str(_u.Dc6.site[num].Pl));
    }
  }
}

void QZQSM::decode_dc6()
{
  _u.Dc6.Tp = get_val(53, 3);
  int num;
  for (num = 0; num < 5; num++) {
    _u.Dc6.site[num].TaD = get_val(56 + (28 * num), 1);
    _u.Dc6.site[num].TaH = get_val(57 + (28 * num), 5);
    _u.Dc6.site[num].TaM = get_val(62 + (28 * num), 6);
    _u.Dc6.site[num].Th  = get_val(68 + (28 * num), 9);
    _u.Dc6.site[num].Pl  = get_val(77 + (28 * num), 7);
    if ((_u.Dc6.site[num].TaH != 31) && (_u.Dc6.site[num].TaM != 63)) {
      utc2jst(_Header.AtMo, _Header.AtD, _u.Dc6.site[num].TaH, _u.Dc6.site[num].TaM);
    }
  }
}
#endif // QZQSM_ENABLE_DC6

//===============================================================
// Disaster Category Code 8
// JMA-DC Report (Volcano)

#ifdef QZQSM_ENABLE_DC8

#define DC8_REPORT \
   "Disaster alert (volcano) (%s)\n\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n" \
   "volcano name: %s\n" \
   "Date: %s\n" \
   "Phenomenon: %s\n" \

#define DC8_REPORT2 \
   "%s\n"

// Activity Time
const char* QZQSM::dc8td2str(int d, int h, int m, int ambiguity)
{
   if (ambiguity <= 3) {
     snprintf(_undefMessage, sizeof(_undefMessage),
              "%d days %d hours %d minutes", d, h, m);
   } else if (ambiguity == 4) {
     snprintf(_undefMessage, sizeof(_undefMessage),
              "%d days %d hours", d, h);
   } else if (ambiguity == 5) {
     snprintf(_undefMessage, sizeof(_undefMessage),
              "%d days", d);
   } else {
     return "unknown";
   }

   return _undefMessage;
}

// Warning Code
const char* QZQSM::dc8dw2str(int code)
{
   switch (code) {
   case 1: return "eruption alert";
   case 2: return "alert around crater";
   case 3: return "eruption warning (surrounding waters)";
   case 4: return "Eruption forecast: Alert cleared";
   case 5: return "eruption forecast";
   case 11: return "Level 1 (note that this is an active volcano)";
   case 12: return "Level 2 (regulation around crater)";
   case 13: return "Level 3 (mountain access restricted)";
   case 14: return "Level 4 (prepare for evacuation)";
   case 15: return "Level 5 (evacuation)";
   case 21: return "Note that this is an active volcano";
   case 22: return "Danger around crater";
   case 23: return "Mountain danger";
   case 24: return "Severe foot warning";
   case 25: return "Severe alert for residential area";
   case 31: return "marine alert (volcanic alert)";
   case 32: return "marine warning (volcanic eruption warning canceled)";
   case 33: return "Ocean Forecast (Eruption Forecast)";
   case 35: return "Note that this is an active volcano (submarine volcano)";
   case 36: return "surrounding sea area alert";
   case 41: return "Eruption warning: Evacuation, etc.";
   case 42: return "Eruption warning: access restrictions, etc.";
   case 43: return "Warning around the crater: entry restrictions, etc.";
   case 44: return "Eruption warning (surrounding waters): Surrounding waters warning";
   case 45: return "Note that this is an active volcano";
   case 46: return "Eruption alert: Serious alert for the residential area";
   case 47: return "Eruption alert: Severe alert at the foot of the volcano";
   case 48: return "Eruption alert: Warning around crater";
   case 49: return "Warning around crater: Warning around crater";
   case 51: return "explosion";
   case 52: return "eruption";
   case 53: return "eruption start";
   case 54: return "Continuous eruption continues";
   case 55: return "continuous eruption stop";
   case 56: return "frequent eruptions";
   case 61: return "looks like it exploded";
   case 62: return "It seems to have erupted";
   case 63: return "The eruption seems to have started";
   case 64: return "Continuous eruptions seem to continue";
   case 65: return "Continuous eruptions seem to have stopped";
   case 91: return "unknown";
   case 99: return "Other phenomena";
   case 127: return "Other disaster prevention weather information elements";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Disaster weather information element (code number: %d)", code);
     return _undefMessage;
   }
}

// Volcano name
const char* QZQSM::dc8vo2str(int code)
{
  switch (code) {
case 101: return "Shiretoko Iouzan";
   case 102: return "Mt. Rausu";
   case 103: return "Mashu";
   case 104: return "Atosanupuri";
   case 105: return "Meakandake";
   case 106: return "Maruyama";
   case 107: return "Daisetsuzan";
   case 108: return "Tokachidake";
   case 109: return "Mt. Tarumae";
   case 110: return "Eniwadake";
   case 111: return "Kuttaraku";
   case 112: return "Usuzan";
   case 113: return "Hokkaido Komagatake";
   case 114: return "Esan";
   case 115: return "Oshima Oshima";
   case 116: return "Mount Rishiri";
   case 117: return "Mt. Yotei";
   case 118: return "Niseko";
   case 119: return "zenzenzan";
   case 120: return "Mount Oakan";
   case 151: return "Moyodake";
   case 152: return "Spray Mountain";
   case 153: return "Mt. Shiusu";
   case 154: return "Moeyama Oda";
   case 155: return "Etorofu Yakeyama";
   case 156: return "Mt. Etorofu Atosa";
   case 157: return "Mount Bertalbe";
   case 158: return "Mt.";
   case 159: return "Mount Rausu";
   case 160: return "Tomariyama";
   case 161: return "Mt. Rurui";
   case 201: return "Osorezan";
   case 202: return "Mount Iwaki";
   case 203: return "Mount Hakkoda";
   case 204: return "Towada";
   case 205: return "Akita Yakeyama";
   case 206: return "Hachimantai";
   case 207: return "Mount Iwate";
   case 208: return "Akita Komagatake";
   case 209: return "Mt. Chokai";
   case 210: return "Mount Kurikoma";
   case 211: return "Naruko";
   case 212: return "Mt. Zao";
   case 213: return "Mount Azuma";
   case 214: return "Adatarayama";
   case 215: return "Mount Bandai";
   case 216: return "Mt. Hiuchigatake";
   case 217: return "Hijiori";
   case 218: return "swamp";
   case 301: return "Nasudake";
   case 302: return "Mount Nikko Shirane";
   case 303: return "Mount Akagi";
   case 304: return "Mt.Haruna";
   case 305: return "Mount Kusatsu-Shirane";
   case 306: return "Mount Asama";
   case 307: return "Niigata Yakeyama";
   case 308: return "Mount Myoko";
   case 309: return "Midagahara";
   case 310: return "Yakedake";
   case 311: return "Mt.Norikura";
   case 312: return "Mount Ontake";
   case 313: return "Hakusan";
   case 314: return "Mt.Fuji";
   case 315: return "Mount Hakone";
   case 316: return "Tobu Izu Volcanoes";
   case 317: return "Izu Oshima";
   case 318: return "Niijima";
   case 319: return "Kozushima";
   case 320: return "Miyakejima";
   case 321: return "Hachijojima";
   case 322: return "Aogashima";
   case 323: return "Bayonnaise Rocks";
   case 324: return "Sumisu Island";
   case 325: return "Izu Torishima";
   case 326: return "Nishinoshima";
   case 327: return "Haitoku Seamount";
   case 328: return "Eruption Asane";
   case 329: return "Iwo Jima";
   case 330: return "Beifudetai";
   case 331: return "Fukuokanoba";
   case 333: return "Mount Takahara";
   case 334: return "Yokodake";
   case 335: return "Mount Akandana";
   case 336: return "Toshima";
   case 337: return "Mikurashima";
   case 338: return "Sofu Rock";
   case 339: return "Umigata Seamount";
   case 340: return "Minamihiyoshi Seamount";
   case 341: return "Nikko Seamount";
   case 342: return "Mount Nantai";
   case 350: return "Mt. Kusatsu-Shirane (Mt. Shirane (near Yugama))";
   case 351: return "Mt. Kusatsu-Shirane (Mt. Moto-Shirane)";
   case 401: return "Mount Sanbe";
   case 502: return "Kujuyama";
   case 503: return "Mount Aso";
   case 504: return "Mount Unzen";
   case 505: return "Mount Kirishima";
   case 506: return "Sakurajima";
   case 507: return "Kaimondake";
   case 508: return "Satsuma Iwo Jima";
   case 509: return "Kuchinoerabujima";
   case 510: return "Nakanoshima";
   case 511: return "Suwanosejima";
   case 512: return "Abu volcanoes";
   case 513: return "Tsurumidake/Garandake";
   case 514: return "Yufudake";
   case 515: return "Fukue Volcanoes";
   case 516: return "Yonemaru/Sumiyoshiike";
   case 517: return "Wakamiko";
   case 518: return "Ikeda/Yamakawa";
   case 519: return "Kuchinoshima";
   case 550: return "Mount Kirishima (Ohachi)";
   case 551: return "Mt. Kirishima (Mt. Shinmoe)";
   case 552: return "Mt. Kirishima (around Ebino Kogen (Mt. Iou))";
   case 553: return "Mount Kirishima (Ohata Pond)";
   case 601: return "Iwo Torishima";
   case 602: return "Submarine volcano north-northeast of Iriomote Island";
   case 900: return "active volcanoes nationwide";
   case 901: return "other active volcanoes";
   case 902: return "new active volcano";
   case 4000: return "other volcanoes";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "volcano (code number: %d)", code);
     return _undefMessage;
  }
}
#endif // QZQSM_ENABLE_DC8

#if defined(QZQSM_ENABLE_DC8) || defined(QZQSM_ENABLE_DC9)

// Local Government
const char* QZQSM::dc8pl2str(int code)
{
  switch (code) {
case 110000: return "Sapporo, Hokkaido";
   case 120200: return "Hakodate, Hokkaido";
   case 120300: return "Otaru, Hokkaido";
   case 120400: return "Asahikawa, Hokkaido";
   case 120500: return "Muroran City, Hokkaido";
   case 120600: return "Kushiro, Hokkaido";
   case 120700: return "Obihiro, Hokkaido";
   case 120800: return "Kitami City, Hokkaido";
   case 120900: return "Yubari, Hokkaido";
   case 121000: return "Iwamizawa, Hokkaido";
   case 121100: return "Abashiri, Hokkaido";
   case 121200: return "Rumoi, Hokkaido";
   case 121300: return "Tomakomai, Hokkaido";
   case 121400: return "Wakkanai, Hokkaido";
   case 121500: return "Bibai City, Hokkaido";
   case 121600: return "Ashibetsu, Hokkaido";
   case 121700: return "Ebetsu, Hokkaido";
   case 121800: return "Akabira, Hokkaido";
   case 121900: return "Monbetsu, Hokkaido";
   case 122000: return "Shibetsu, Hokkaido";
   case 122100: return "Nayoro, Hokkaido";
   case 122200: return "Mikasa, Hokkaido";
   case 122300: return "Nemuro, Hokkaido";
   case 122400: return "Chitose, Hokkaido";
   case 122500: return "Takigawa City, Hokkaido";
   case 122600: return "Sunagawa City, Hokkaido";
   case 122700: return "Utashinai City, Hokkaido";
   case 122800: return "Fukagawa, Hokkaido";
   case 122900: return "Furano, Hokkaido";
   case 123000: return "Noboribetsu, Hokkaido";
   case 123100: return "Eniwa City, Hokkaido";
   case 123300: return "Date City, Hokkaido";
   case 123400: return "Kitahiroshima, Hokkaido";
   case 123500: return "Ishikari, Hokkaido";
   case 123600: return "Hokuto City, Hokkaido";
   case 130300: return "Tobetsu, Hokkaido";
   case 130400: return "Hokkaido Shinshinotsu Village";
   case 133100: return "Matsumae, Hokkaido";
   case 133200: return "Hokkaido Fukushima Town";
   case 133300: return "Hokkaido Shiriuchi";
   case 133400: return "Kikonai, Hokkaido";
   case 133700: return "Nanae, Hokkaido";
   case 134300: return "Hokkaido Shikabe";
   case 134500: return "Hokkaido Morimachi";
   case 134600: return "Yakumo, Hokkaido";
   case 134700: return "Oshamanbe, Hokkaido";
   case 136100: return "Esashi Town, Hokkaido";
   case 136200: return "Kaminokuni, Hokkaido";
   case 136300: return "Hokkaido Assabu Town";
   case 136400: return "Otobe, Hokkaido";
   case 136700: return "Hokkaido Okushiri";
   case 137000: return "Imaganecho, Hokkaido";
   case 137100: return "Hokkaido Setana Town";
   case 139100: return "Hokkaido Shimamaki Village";
   case 139200: return "Hokkaido Suttsu";
   case 139300: return "Kuromatsunai Town, Hokkaido";
   case 139400: return "Rankoshi, Hokkaido";
   case 139500: return "Niseko Town, Hokkaido";
   case 139600: return "Hokkaido Makkari Village";
   case 139700: return "Hokkaido Rusutsu Village";
   case 139800: return "Kimobetsu, Hokkaido";
   case 139900: return "Hokkaido Kyogoku";
   case 140000: return "Kutchan, Hokkaido";
   case 140100: return "Hokkaido Kyowa Town";
   case 140200: return "Iwanai, Hokkaido";
   case 140300: return "Hokkaido Tomari Village";
   case 140400: return "Hokkaido Kamoenai Village";
   case 140500: return "Shakotan, Hokkaido";
   case 140600: return "Furubira, Hokkaido";
   case 140700: return "Niki, Hokkaido";
   case 140800: return "Yoichi, Hokkaido";
   case 140900: return "Akaigawa Village, Hokkaido";
   case 142300: return "Namporo Town, Hokkaido";
   case 142400: return "Hokkaido Naie Town";
   case 142500: return "Hokkaido Kamisunagawa";
   case 142700: return "Yuni Town, Hokkaido";
   case 142800: return "Hokkaido Naganuma";
   case 142900: return "Kuriyama, Hokkaido";
   case 143000: return "Tsukigata, Hokkaido";
   case 143100: return "Hokkaido Urausu Town";
   case 143200: return "Shintotsukawa, Hokkaido";
   case 143300: return "Hokkaido Imoseushicho";
   case 143400: return "Chichibubetsu, Hokkaido";
   case 143600: return "Uryu Town, Hokkaido";
   case 143700: return "Hokuryu, Hokkaido";
   case 143800: return "Numata, Hokkaido";
   case 145200: return "Takasu, Hokkaido";
   case 145300: return "Higashikaguracho, Hokkaido";
   case 145400: return "Toma Town, Hokkaido";
   case 145500: return "Hippu, Hokkaido";
   case 145600: return "Hokkaido Aibetsu";
   case 145700: return "Kamikawa Town, Hokkaido";
   case 145800: return "Higashikawa, Hokkaido";
   case 145900: return "Biei, Hokkaido";
case 146000: return "Kamifurano, Hokkaido";
   case 146100: return "Nakafurano, Hokkaido";
   case 146200: return "Hokkaido Minamifurano";
   case 146300: return "Hokkaido Shimukappu Village";
   case 146400: return "Wasamu, Hokkaido";
   case 146500: return "Hokkaido Kenbuchi";
   case 146800: return "Hokkaido Shimokawa";
   case 146900: return "Bifuka, Hokkaido";
   case 147000: return "Hokkaido Otoineppu Village";
   case 147100: return "Nakagawacho, Hokkaido";
   case 147200: return "Hokkaido Horokanai Town";
   case 148100: return "Mashike, Hokkaido";
   case 148200: return "Kodaira, Hokkaido";
   case 148300: return "Hokkaido Tomamae Town";
   case 148400: return "Haboro Town, Hokkaido";
   case 148500: return "Hatsuyamabetsu Village, Hokkaido";
   case 148600: return "Enbetsu, Hokkaido";
   case 148700: return "Hokkaido Teshio Town";
   case 151100: return "Hokkaido Sarufutsu Village";
   case 151200: return "Hokkaido Hamatonbetsu";
   case 151300: return "Nakatonbetsu, Hokkaido";
   case 151400: return "Esachicho, Hokkaido";
   case 151600: return "Hokkaido Toyotomi";
   case 151700: return "Rebun Town, Hokkaido";
   case 151800: return "Rishiri, Hokkaido";
   case 151900: return "Rishirifuji Town, Hokkaido";
   case 152000: return "Horonobe Town, Hokkaido";
   case 154300: return "Bihoro, Hokkaido";
   case 154400: return "Tsubetsu, Hokkaido";
   case 154500: return "Shari, Hokkaido";
   case 154600: return "Kiyosato, Hokkaido";
   case 154700: return "Koshimizu, Hokkaido";
   case 154900: return "Hokkaido Kunneppu";
   case 155000: return "Oketo Town, Hokkaido";
   case 155200: return "Hokkaido Saroma Town";
   case 155500: return "Hokkaido Engaru Town";
   case 155900: return "Yubetsu, Hokkaido";
   case 156000: return "Takinoue, Hokkaido";
   case 156100: return "Hokkaido Okoppe";
   case 156200: return "Hokkaido Nishikobu Village";
   case 156300: return "Oumucho, Hokkaido";
   case 156400: return "Ozora Town, Hokkaido";
   case 157100: return "Toyoura Town, Hokkaido";
   case 157500: return "Sobetsu, Hokkaido";
   case 157800: return "Shiraoi, Hokkaido";
   case 158100: return "Atsuma, Hokkaido";
   case 158400: return "Toyako, Hokkaido";
   case 158500: return "Abira, Hokkaido";
   case 158600: return "Mukawa, Hokkaido";
   case 160100: return "Hidaka, Hokkaido";
   case 160200: return "Biratori, Hokkaido";
   case 160400: return "Hokkaido Niikappu";
   case 160700: return "Urakawacho, Hokkaido";
   case 160800: return "Hokkaido Samani Town";
   case 160900: return "Hokkaido Erimo Town";
   case 161000: return "Hokkaido Shinhidaka Town";
   case 163100: return "Otofuke, Hokkaido";
   case 163200: return "Shihoro, Hokkaido";
   case 163300: return "Kamishihoro, Hokkaido";
   case 163400: return "Hokkaido Shikaoi";
   case 163500: return "Shintoku, Hokkaido";
   case 163600: return "Shimizu, Hokkaido";
   case 163700: return "Memuro, Hokkaido";
   case 163800: return "Nakasatsunai Village, Hokkaido";
   case 163900: return "Hokkaido Sarabetsu Village";
   case 164100: return "Taikicho, Hokkaido";
   case 164200: return "Hiroo Town, Hokkaido";
   case 164300: return "Makubetsu, Hokkaido";
   case 164400: return "Ikeda Town, Hokkaido";
   case 164500: return "Hokkaido Toyokoro";
   case 164600: return "Hokkaido Honbetsu";
   case 164700: return "Hokkaido Ashoro";
   case 164800: return "Rikubetsu, Hokkaido";
   case 164900: return "Urahoro, Hokkaido";
   case 166100: return "Kushiro, Hokkaido";
   case 166200: return "Akkeshi, Hokkaido";
   case 166300: return "Hokkaido Hamanaka";
   case 166400: return "Hokkaido Shibecha";
   case 166500: return "Hokkaido Teshikaga";
   case 166700: return "Hokkaido Tsurui Village";
   case 166800: return "Hokkaido Shiranuka";
   case 169001: return "Hokkaido Kunashiri Island";
   case 169002: return "Etorofu Island, Hokkaido";
   case 169100: return "Betsukai, Hokkaido";
   case 169200: return "Nakashibetsu, Hokkaido";
   case 169300: return "Shibetsu, Hokkaido";
   case 169400: return "Rausu, Hokkaido";
   case 169500: return "Hokkaido Shikotan Village";
   case 199999: return "Other municipalities in Hokkaido";
   case 220100: return "Aomori City, Aomori Prefecture";
case 220200: return "Hirosaki City, Aomori Prefecture";
   case 220300: return "Hachinohe City, Aomori Prefecture";
   case 220400: return "Kuroishi City, Aomori Prefecture";
   case 220500: return "Goshogawara City, Aomori Prefecture";
   case 220600: return "Towada City, Aomori Prefecture";
   case 220700: return "Misawa City, Aomori Prefecture";
   case 220800: return "Mutsu City, Aomori Prefecture";
   case 220900: return "Tsugaru City, Aomori Prefecture";
   case 221000: return "Hirakawa City, Aomori Prefecture";
   case 230100: return "Hiranai Town, Aomori Prefecture";
   case 230300: return "Imabetsu Town, Aomori Prefecture";
   case 230400: return "Yomogi Tamura, Aomori Prefecture";
   case 230700: return "Sotogahama Town, Aomori Prefecture";
   case 232100: return "Ajigasawa Town, Aomori Prefecture";
   case 232300: return "Fukaura Town, Aomori Prefecture";
   case 234300: return "Nishimeya Village, Aomori Prefecture";
   case 236100: return "Fujisaki, Aomori";
   case 236200: return "Owani Town, Aomori Prefecture";
   case 236700: return "Inakadate Village, Aomori Prefecture";
   case 238100: return "Itayanagi Town, Aomori Prefecture";
   case 238400: return "Tsuruta, Aomori Prefecture";
   case 238700: return "Nakadomari, Aomori Prefecture";
   case 240100: return "Noheji, Aomori Prefecture";
   case 240200: return "Shichinohe Town, Aomori Prefecture";
   case 240500: return "Rokunohe, Aomori Prefecture";
   case 240600: return "Yokohama, Aomori Prefecture";
   case 240800: return "Tohoku Town, Aomori Prefecture";
   case 241100: return "Rokkasho Village, Aomori Prefecture";
   case 241200: return "Oirase Town, Aomori Prefecture";
   case 242300: return "Oma Town, Aomori Prefecture";
   case 242400: return "Higashidori Village, Aomori Prefecture";
   case 242500: return "Kazamaura Village, Aomori Prefecture";
   case 242600: return "Sai Village, Aomori Prefecture";
   case 244100: return "Sannohe Town, Aomori Prefecture";
   case 244200: return "Gonohe, Aomori Prefecture";
   case 244300: return "Tago Town, Aomori Prefecture";
   case 244500: return "Nanbu Town, Aomori Prefecture";
   case 244600: return "Hashikami, Aomori Prefecture";
   case 245000: return "Shingo Village, Aomori Prefecture";
   case 299999: return "Other municipalities in Aomori Prefecture";
   case 320100: return "Morioka City, Iwate Prefecture";
   case 320200: return "Miyako City, Iwate Prefecture";
   case 320300: return "Ofunato City, Iwate Prefecture";
   case 320500: return "Hanamaki City, Iwate Prefecture";
   case 320600: return "Kitakami City, Iwate Prefecture";
   case 320700: return "Kuji City, Iwate Prefecture";
   case 320800: return "Tono City, Iwate Prefecture";
   case 320900: return "Ichinoseki City, Iwate Prefecture";
   case 321000: return "Rikuzentakata City, Iwate Prefecture";
   case 321100: return "Kamaishi City, Iwate Prefecture";
   case 321300: return "Ninohe City, Iwate Prefecture";
   case 321400: return "Hachimantai City, Iwate Prefecture";
   case 321500: return "Oshu City, Iwate Prefecture";
   case 321600: return "Takizawa City, Iwate Prefecture";
   case 330100: return "Shizukuishi Town, Iwate Prefecture";
   case 330200: return "Kuzumaki Town, Iwate Prefecture";
   case 330300: return "Iwate Town, Iwate Prefecture";
   case 332100: return "Shiwa Town, Iwate Prefecture";
   case 332200: return "Yahabacho, Iwate Prefecture";
   case 336600: return "Nishiwaga Town, Iwate Prefecture";
   case 338100: return "Kanegasaki Town, Iwate Prefecture";
   case 340200: return "Hiraizumi, Iwate Prefecture";
   case 344100: return "Sumita, Iwate Prefecture";
   case 346100: return "Otsuchi Town, Iwate Prefecture";
   case 348200: return "Yamada, Iwate Prefecture";
   case 348300: return "Iwaizumi Town, Iwate Prefecture";
   case 348400: return "Tanohata Village, Iwate Prefecture";
   case 348500: return "Fudai Village, Iwate Prefecture";
   case 350100: return "Karumai Town, Iwate Prefecture";
   case 350300: return "Noda Village, Iwate Prefecture";
   case 350600: return "Kunohe Village, Iwate Prefecture";
   case 350700: return "Hirono Town, Iwate Prefecture";
   case 352400: return "Ichinohe Town, Iwate Prefecture";
   case 399999: return "Other municipalities in Iwate Prefecture";
   case 410000: return "Sendai City, Miyagi Prefecture";
   case 420200: return "Ishinomaki City, Miyagi Prefecture";
   case 420300: return "Shiogama City, Miyagi Prefecture";
   case 420500: return "Kesennuma City, Miyagi Prefecture";
   case 420600: return "Shiroishi City, Miyagi Prefecture";
   case 420700: return "Natori City, Miyagi Prefecture";
   case 420800: return "Kakuda City, Miyagi Prefecture";
   case 420900: return "Tagajo City, Miyagi Prefecture";
   case 421100: return "Iwanuma City, Miyagi Prefecture";
   case 421200: return "Tome City, Miyagi Prefecture";
   case 421300: return "Kurihara City, Miyagi Prefecture";
   case 421400: return "Higashimatsushima City, Miyagi Prefecture";
   case 421500: return "Osaki City, Miyagi Prefecture";
   case 421600: return "Tomiya City, Miyagi Prefecture";
   case 430100: return "Zao Town, Miyagi Prefecture";
   case 430200: return "Shichikashuku Town, Miyagi Prefecture";
   case 432100: return "Ogawara, Miyagi Prefecture";
   case 432200: return "Murata Town, Miyagi Prefecture";
   case 432300: return "Shibata, Miyagi Prefecture";
   case 432400: return "Kawasaki, Miyagi Prefecture";
   case 434100: return "Marumori, Miyagi Prefecture";
   case 436100: return "Watari Town, Miyagi Prefecture";
   case 436200: return "Yamamoto, Miyagi Prefecture";
   case 440100: return "Matsushima, Miyagi Prefecture";
   case 440400: return "Shichigahama Town, Miyagi Prefecture";
   case 440600: return "Rifu, Miyagi Prefecture";
   case 442100: return "Yamato, Miyagi Prefecture";
   case 442200: return "Osato Town, Miyagi Prefecture";
   case 442400: return "Ohira Village, Miyagi Prefecture";
   case 444400: return "Shikama Town, Miyagi Prefecture";
   case 444500: return "Kamicho, Miyagi Prefecture";
   case 450100: return "Wakuya Town, Miyagi Prefecture";
   case 450500: return "Misato Town, Miyagi Prefecture";
   case 458100: return "Onagawa, Miyagi Prefecture";
   case 460600: return "Minamisanriku Town, Miyagi Prefecture";
   case 499999: return "Other municipalities in Miyagi Prefecture";
   case 520100: return "Akita City, Akita Prefecture";
   case 520200: return "Noshiro City, Akita Prefecture";
   case 520300: return "Yokote City, Akita Prefecture";
   case 520400: return "Odate City, Akita Prefecture";
   case 520600: return "Oga City, Akita Prefecture";
   case 520700: return "Yuzawa, Akita Prefecture";
   case 520900: return "Kazuno City, Akita Prefecture";
   case 521000: return "Yurihonjo City, Akita Prefecture";
   case 521100: return "Katagami City, Akita Prefecture";
   case 521200: return "Daisen, Akita Prefecture";
   case 521300: return "Kitaakita City, Akita Prefecture";
case 521400: return "Nikaho City, Akita Prefecture";
   case 521500: return "Semboku, Akita";
   case 530300: return "Kosaka Town, Akita Prefecture";
   case 532700: return "Kamikoani Village, Akita Prefecture";
   case 534600: return "Fujisato, Akita Prefecture";
   case 534800: return "Mitane Town, Akita Prefecture";
   case 534900: return "Happo, Akita Prefecture";
   case 536100: return "Gojome Town, Akita Prefecture";
   case 536300: return "Hachirogata Town, Akita Prefecture";
   case 536600: return "Ikawa Town, Akita Prefecture";
   case 536800: return "Ogata Village, Akita Prefecture";
   case 543400: return "Misato Town, Akita Prefecture";
   case 546300: return "Ugo Town, Akita Prefecture";
   case 546400: return "Higashinaruse, Akita Prefecture";
   case 599999: return "Other municipalities in Akita Prefecture";
   case 620100: return "Yamagata City, Yamagata Prefecture";
   case 620200: return "Yonezawa City, Yamagata Prefecture";
   case 620300: return "Tsuruoka City, Yamagata Prefecture";
   case 620400: return "Sakata City, Yamagata Prefecture";
   case 620500: return "Shinjo City, Yamagata Prefecture";
   case 620600: return "Sagae City, Yamagata Prefecture";
   case 620700: return "Kaminoyama City, Yamagata Prefecture";
   case 620800: return "Murayama City, Yamagata Prefecture";
   case 620900: return "Nagai City, Yamagata Prefecture";
   case 621000: return "Tendo City, Yamagata Prefecture";
   case 621100: return "Higashine City, Yamagata Prefecture";
   case 621200: return "Obanazawa City, Yamagata Prefecture";
   case 621300: return "Nanyo City, Yamagata Prefecture";
   case 630100: return "Yamanobe, Yamagata Prefecture";
   case 630200: return "Nakayama Town, Yamagata Prefecture";
   case 632100: return "Kahoku Town, Yamagata Prefecture";
   case 632200: return "Nishikawa Town, Yamagata Prefecture";
   case 632300: return "Asahi Town, Yamagata Prefecture";
   case 632400: return "Oe Town, Yamagata Prefecture";
   case 634100: return "Oishida Town, Yamagata Prefecture";
   case 636100: return "Kanayama Town, Yamagata Prefecture";
   case 636200: return "Mogami Town, Yamagata Prefecture";
   case 636300: return "Funagata Town, Yamagata Prefecture";
   case 636400: return "Mamurogawa Town, Yamagata Prefecture";
   case 636500: return "Okura Village, Yamagata Prefecture";
   case 636600: return "Sakegawa Village, Yamagata Prefecture";
   case 636700: return "Tozawa Village, Yamagata Prefecture";
   case 638100: return "Takahata Town, Yamagata Prefecture";
   case 638200: return "Kawanishi Town, Yamagata Prefecture";
   case 640100: return "Oguni Town, Yamagata Prefecture";
   case 640200: return "Shirataka Town, Yamagata Prefecture";
   case 640300: return "Iide Town, Yamagata Prefecture";
   case 642600: return "Mikawa Town, Yamagata Prefecture";
   case 642800: return "Shonai Town, Yamagata Prefecture";
   case 646100: return "Yusa Town, Yamagata Prefecture";
   case 699999: return "Other municipalities in Yamagata Prefecture";
   case 720100: return "Fukushima City, Fukushima Prefecture";
   case 720200: return "Aizuwakamatsu City, Fukushima Prefecture";
   case 720300: return "Koriyama City, Fukushima Prefecture";
   case 720400: return "Iwaki City, Fukushima Prefecture";
   case 720500: return "Shirakawa City, Fukushima Prefecture";
   case 720700: return "Sukagawa City, Fukushima Prefecture";
   case 720800: return "Kitakata City, Fukushima Prefecture";
   case 720900: return "Soma City, Fukushima Prefecture";
   case 721000: return "Nihonmatsu City, Fukushima Prefecture";
   case 721100: return "Tamura City, Fukushima Prefecture";
   case 721200: return "Minamisoma City, Fukushima Prefecture";
   case 721300: return "Date City, Fukushima Prefecture";
   case 721400: return "Motomiya City, Fukushima Prefecture";
   case 730100: return "Kouori Town, Fukushima Prefecture";
   case 730300: return "Kunimi Town, Fukushima Prefecture";
   case 730800: return "Kawamata Town, Fukushima Prefecture";
   case 732200: return "Otama Village, Fukushima Prefecture";
   case 734200: return "Kagamiishi Town, Fukushima Prefecture";
   case 734400: return "Tenei Village, Fukushima Prefecture";
   case 736200: return "Shimogo Town, Fukushima Prefecture";
   case 736400: return "Hinoemata Village, Fukushima Prefecture";
   case 736700: return "Tadami Town, Fukushima Prefecture";
   case 736800: return "Minamiaizu Town, Fukushima Prefecture";
   case 740200: return "Kitashiobara Village, Fukushima Prefecture";
   case 740500: return "Nishiaizu Town, Fukushima Prefecture";
   case 740700: return "Bandai Town, Fukushima Prefecture";
   case 740800: return "Inawashiro Town, Fukushima Prefecture";
   case 742100: return "Aizusakashita Town, Fukushima Prefecture";
   case 742200: return "Yukawa Village, Fukushima Prefecture";
   case 742300: return "Yanaizu Town, Fukushima Prefecture";
   case 744400: return "Mishima Town, Fukushima Prefecture";
   case 744500: return "Kanayama Town, Fukushima Prefecture";
   case 744600: return "Showa Village, Fukushima Prefecture";
   case 744700: return "Aizumisato Town, Fukushima Prefecture";
   case 746100: return "Nishigo Village, Fukushima Prefecture";
   case 746400: return "Izumizaki Village, Fukushima Prefecture";
   case 746500: return "Nakashima Village, Fukushima Prefecture";
   case 746600: return "Yabuki Town, Fukushima Prefecture";
   case 748100: return "Tanagura Town, Fukushima Prefecture";
   case 748200: return "Fukushima Yamatsuri Town";
   case 748300: return "Hanawa Town, Fukushima Prefecture";
   case 748400: return "Samegawa Village, Fukushima Prefecture";
   case 750100: return "Ishikawa Town, Fukushima Prefecture";
   case 750200: return "Tamagawa Village, Fukushima Prefecture";
   case 750300: return "Hirata Village, Fukushima Prefecture";
   case 750400: return "Asakawa Town, Fukushima Prefecture";
   case 750500: return "Furudono, Fukushima Prefecture";
   case 752100: return "Miharu Town, Fukushima Prefecture";
   case 752200: return "Ono Town, Fukushima Prefecture";
   case 754100: return "Hirono Town, Fukushima Prefecture";
   case 754200: return "Naraha Town, Fukushima Prefecture";
   case 754300: return "Tomioka Town, Fukushima Prefecture";
   case 754400: return "Kawauchi Village, Fukushima Prefecture";
   case 754500: return "Okuma Town, Fukushima Prefecture";
   case 754600: return "Futaba Town, Fukushima Prefecture";
   case 754700: return "Namie Town, Fukushima Prefecture";
   case 754800: return "Katsurao, Fukushima Prefecture";
   case 756100: return "Shinchi Town, Fukushima Prefecture";
   case 756400: return "Iidate, Fukushima Prefecture";
   case 799999: return "Other municipalities in Fukushima Prefecture";
   case 820100: return "Mito City, Ibaraki Prefecture";
   case 820200: return "Hitachi City, Ibaraki Prefecture";
   case 820300: return "Tsuchiura City, Ibaraki Prefecture";
   case 820400: return "Koga City, Ibaraki Prefecture";
   case 820500: return "Ishioka City, Ibaraki Prefecture";
   case 820700: return "Yuki City, Ibaraki Prefecture";
   case 820800: return "Ryugasaki City, Ibaraki Prefecture";
   case 821000: return "Shimotsuma City, Ibaraki Prefecture";
   case 821100: return "Joso City, Ibaraki Prefecture";
   case 821200: return "Hitachiota City, Ibaraki Prefecture";
case 821400: return "Takahagi City, Ibaraki Prefecture";
   case 821500: return "Kitaibaraki City, Ibaraki Prefecture";
   case 821600: return "Kasama City, Ibaraki Prefecture";
   case 821700: return "Toride City, Ibaraki Prefecture";
   case 821900: return "Ushiku City, Ibaraki Prefecture";
   case 822000: return "Tsukuba City, Ibaraki Prefecture";
   case 822100: return "Hitachinaka City, Ibaraki Prefecture";
   case 822200: return "Kashima City, Ibaraki Prefecture";
   case 822300: return "Itako City, Ibaraki Prefecture";
   case 822400: return "Moriya City, Ibaraki Prefecture";
   case 822500: return "Hitachiomiya City, Ibaraki Prefecture";
   case 822600: return "Naka City, Ibaraki Prefecture";
   case 822700: return "Chikusei City, Ibaraki Prefecture";
   case 822800: return "Bando City, Ibaraki Prefecture";
   case 822900: return "Inashiki, Ibaraki";
   case 823000: return "Kasumigaura City, Ibaraki Prefecture";
   case 823100: return "Sakuragawa City, Ibaraki Prefecture";
   case 823200: return "Kamisu City, Ibaraki Prefecture";
   case 823300: return "Namegata City, Ibaraki Prefecture";
   case 823400: return "Hokota City, Ibaraki Prefecture";
   case 823500: return "Tsukubamirai City, Ibaraki Prefecture";
   case 823600: return "Omitama City, Ibaraki Prefecture";
   case 830200: return "Ibaraki, Ibaraki";
   case 830900: return "Oarai Town, Ibaraki Prefecture";
   case 831000: return "Shirosato, Ibaraki Prefecture";
   case 834100: return "Tokai Village, Ibaraki Prefecture";
   case 836400: return "Daigo Town, Ibaraki Prefecture";
   case 844200: return "Miura Village, Ibaraki Prefecture";
   case 844300: return "Ami Town, Ibaraki Prefecture";
   case 844700: return "Kawachi, Ibaraki";
   case 852100: return "Yachiyo, Ibaraki Prefecture";
   case 854200: return "Goka Town, Ibaraki Prefecture";
   case 854600: return "Sakaimachi, Ibaraki";
   case 856400: return "Tone Town, Ibaraki Prefecture";
   case 899999: return "Other municipalities in Ibaraki Prefecture";
   case 920100: return "Utsunomiya City, Tochigi Prefecture";
   case 920200: return "Ashikaga City, Tochigi Prefecture";
   case 920300: return "Tochigi City, Tochigi Prefecture";
   case 920400: return "Sano City, Tochigi Prefecture";
   case 920500: return "Kanuma City, Tochigi Prefecture";
   case 920600: return "Nikko City, Tochigi Prefecture";
   case 920800: return "Oyama City, Tochigi Prefecture";
   case 920900: return "Moka City, Tochigi Prefecture";
   case 921000: return "Otawara City, Tochigi Prefecture";
   case 921100: return "Yaita City, Tochigi Prefecture";
   case 921300: return "Nasushiobara City, Tochigi Prefecture";
   case 921400: return "Sakura City, Tochigi Prefecture";
   case 921500: return "Nasukarasuyama City, Tochigi Prefecture";
   case 921600: return "Shimotsuke City, Tochigi Prefecture";
   case 930100: return "Kamimikawa Town, Tochigi Prefecture";
   case 934200: return "Mashiko Town, Tochigi Prefecture";
   case 934300: return "Motegi Town, Tochigi Prefecture";
   case 934400: return "Ichikai, Tochigi Prefecture";
   case 934500: return "Haga Town, Tochigi Prefecture";
   case 936100: return "Mibu Town, Tochigi Prefecture";
   case 936400: return "Nogi, Tochigi Prefecture";
   case 938400: return "Shioya Town, Tochigi Prefecture";
   case 938600: return "Takanezawa Town, Tochigi Prefecture";
   case 940700: return "Nasu Town, Tochigi Prefecture";
   case 941100: return "Nakagawa Town, Tochigi Prefecture";
   case 999999: return "Other municipalities in Tochigi Prefecture";
   case 1020100: return "Maebashi City, Gunma Prefecture";
   case 1020200: return "Takasaki, Gunma";
   case 1020300: return "Kiryu City, Gunma Prefecture";
   case 1020400: return "Isesaki, Gunma";
   case 1020500: return "Ota City, Gunma Prefecture";
   case 1020600: return "Numata City, Gunma Prefecture";
   case 1020700: return "Tatebayashi City, Gunma Prefecture";
   case 1020800: return "Shibukawa, Gunma Prefecture";
   case 1020900: return "Fujioka City, Gunma Prefecture";
   case 1021000: return "Tomioka, Gunma";
   case 1021100: return "Annaka City, Gunma Prefecture";
   case 1021200: return "Midori City, Gunma Prefecture";
   case 1034400: return "Shinto Village, Gunma Prefecture";
   case 1034500: return "Yoshioka, Gunma";
   case 1036600: return "Ueno Village, Gunma Prefecture";
   case 1036700: return "Kanna-cho, Gunma Prefecture";
   case 1038200: return "Shimonita Town, Gunma Prefecture";
   case 1038300: return "Minamimaki Village, Gunma Prefecture";
   case 1038400: return "Kanra Town, Gunma Prefecture";
   case 1042100: return "Nakanojo, Gunma";
   case 1042400: return "Naganohara, Gunma Prefecture";
   case 1042500: return "Tsumagoi, Gunma Prefecture";
   case 1042600: return "Kusatsu, Gunma";
   case 1042800: return "Takayama Village, Gunma Prefecture";
   case 1042900: return "Higashiagatsuma Town, Gunma Prefecture";
   case 1044300: return "Katashina Village, Gunma Prefecture";
   case 1044400: return "Kawaba, Gunma Prefecture";
   case 1044800: return "Showa Village, Gunma Prefecture";
   case 1044900: return "Minakami Town, Gunma Prefecture";
   case 1046400: return "Tamamura Town, Gunma Prefecture";
   case 1052100: return "Itakura Town, Gunma Prefecture";
   case 1052200: return "Meiwa, Gunma";
   case 1052300: return "Chiyoda, Gunma";
   case 1052400: return "Oizumi Town, Gunma Prefecture";
   case 1052500: return "Oura Town, Gunma Prefecture";
   case 1099999: return "Other municipalities in Gunma Prefecture";
   case 1110000: return "Saitama City, Saitama Prefecture";
   case 1120100: return "Kawagoe City, Saitama Prefecture";
   case 1120200: return "Kumagaya, Saitama";
   case 1120300: return "Kawaguchi City, Saitama Prefecture";
   case 1120600: return "Gyoda City, Saitama Prefecture";
   case 1120700: return "Chichibu City, Saitama Prefecture";
   case 1120800: return "Tokorozawa, Saitama Prefecture";
   case 1120900: return "Hanno City, Saitama Prefecture";
   case 1121000: return "Kazo City, Saitama Prefecture";
   case 1121100: return "Honjo City, Saitama Prefecture";
   case 1121200: return "Higashimatsuyama City, Saitama Prefecture";
   case 1121400: return "Kasukabe, Saitama Prefecture";
   case 1121500: return "Sayama, Saitama";
   case 1121600: return "Hanyu City, Saitama Prefecture";
   case 1121700: return "Konosu City, Saitama Prefecture";
   case 1121800: return "Fukaya, Saitama";
   case 1121900: return "Ageo City, Saitama Prefecture";
   case 1122100: return "Soka City, Saitama Prefecture";
   case 1122200: return "Koshigaya City, Saitama Prefecture";
   case 1122300: return "Warabi City, Saitama Prefecture";
   case 1122400: return "Toda City, Saitama Prefecture";
   case 1122500: return "Iruma City, Saitama Prefecture";
   case 1122700: return "Asaka, Saitama";
   case 1122800: return "Shiki City, Saitama Prefecture";
   case 1122900: return "Wako City, Saitama Prefecture";
   case 1123000: return "Niiza City, Saitama Prefecture";
   case 1123100: return "Okegawa City, Saitama Prefecture";
   case 1123200: return "Kuki City, Saitama Prefecture";
   case 1123300: return "Kitamoto City, Saitama Prefecture";
   case 1123400: return "Yashio City, Saitama Prefecture";
   case 1123500: return "Fujimi City, Saitama Prefecture";
case 1123700: return "Misato City, Saitama Prefecture";
   case 1123800: return "Hasuda, Saitama";
   case 1123900: return "Sakado, Saitama Prefecture";
   case 1124000: return "Satte City, Saitama Prefecture";
   case 1124100: return "Tsurugashima City, Saitama Prefecture";
   case 1124200: return "Hidaka, Saitama";
   case 1124300: return "Yoshikawa City, Saitama Prefecture";
   case 1124500: return "Fujimino City, Saitama Prefecture";
   case 1124600: return "Shiraoka City, Saitama Prefecture";
   case 1130100: return "Ina Town, Saitama Prefecture";
   case 1132400: return "Miyoshi, Saitama Prefecture";
   case 1132600: return "Moroyama Town, Saitama Prefecture";
   case 1132700: return "Ogose Town, Saitama Prefecture";
   case 1134100: return "Namegawa Town, Saitama Prefecture";
   case 1134200: return "Arashiyama, Saitama";
   case 1134300: return "Ogawamachi, Saitama Prefecture";
   case 1134600: return "Kawashima, Saitama";
   case 1134700: return "Yoshimicho, Saitama Prefecture";
   case 1134800: return "Hatoyama Town, Saitama Prefecture";
   case 1134900: return "Tokigawa Town, Saitama Prefecture";
   case 1136100: return "Yokoze Town, Saitama Prefecture";
   case 1136200: return "Minano Town, Saitama Prefecture";
   case 1136300: return "Nagatoro Town, Saitama Prefecture";
   case 1136500: return "Ogano Town, Saitama Prefecture";
   case 1136900: return "Higashichichibu, Saitama Prefecture";
   case 1138100: return "Misato, Saitama Prefecture";
   case 1138300: return "Kangawacho, Saitama Prefecture";
   case 1138500: return "Kamisato, Saitama Prefecture";
   case 1140800: return "Yorii Town, Saitama Prefecture";
   case 1144200: return "Miyashiro, Saitama Prefecture";
   case 1146400: return "Sugito Town, Saitama Prefecture";
   case 1146500: return "Matsubushi, Saitama Prefecture";
   case 1199999: return "Other municipalities in Saitama Prefecture";
   case 1210000: return "Chiba City, Chiba Prefecture";
   case 1220200: return "Choshi City, Chiba Prefecture";
   case 1220300: return "Ichikawa City, Chiba Prefecture";
   case 1220400: return "Funabashi, Chiba";
   case 1220500: return "Tateyama City, Chiba Prefecture";
   case 1220600: return "Kisarazu City, Chiba Prefecture";
   case 1220700: return "Matsudo City, Chiba Prefecture";
   case 1220800: return "Noda City, Chiba Prefecture";
   case 1221000: return "Mobara City, Chiba Prefecture";
   case 1221100: return "Narita City, Chiba Prefecture";
   case 1221200: return "Sakura City, Chiba Prefecture";
   case 1221300: return "Togane City, Chiba Prefecture";
   case 1221500: return "Asahi, Chiba";
   case 1221600: return "Narashino City, Chiba Prefecture";
   case 1221700: return "Kashiwa City, Chiba Prefecture";
   case 1221800: return "Katsuura City, Chiba Prefecture";
   case 1221900: return "Ichihara City, Chiba Prefecture";
   case 1222000: return "Nagareyama City, Chiba Prefecture";
   case 1222100: return "Yachiyo City, Chiba Prefecture";
   case 1222200: return "Abiko City, Chiba Prefecture";
   case 1222300: return "Kamogawa City, Chiba Prefecture";
   case 1222400: return "Kamagaya City, Chiba Prefecture";
   case 1222500: return "Kimitsu City, Chiba Prefecture";
   case 1222600: return "Futtsu City, Chiba Prefecture";
   case 1222700: return "Urayasu City, Chiba Prefecture";
   case 1222800: return "Yotsukaido City, Chiba Prefecture";
   case 1222900: return "Sodegaura City, Chiba Prefecture";
   case 1223000: return "Yachimata, Chiba Prefecture";
   case 1223100: return "Inzai City, Chiba Prefecture";
   case 1223200: return "Shirai City, Chiba Prefecture";
   case 1223300: return "Tomisato City, Chiba Prefecture";
   case 1223400: return "Minamiboso City, Chiba Prefecture";
   case 1223500: return "Sosa City, Chiba Prefecture";
   case 1223600: return "Katori City, Chiba Prefecture";
   case 1223700: return "Sanmu City, Chiba Prefecture";
   case 1223800: return "Isumi City, Chiba Prefecture";
   case 1223900: return "Oamishirasato City, Chiba Prefecture";
   case 1232200: return "Shisui Town, Chiba Prefecture";
   case 1232900: return "Sakaecho, Chiba Prefecture";
   case 1234200: return "Kanzakicho, Chiba Prefecture";
   case 1234700: return "Tako Town, Chiba Prefecture";
   case 1234900: return "Tosho Town, Chiba Prefecture";
   case 1240300: return "Kujukuri Town, Chiba Prefecture";
   case 1240900: return "Shibayama Town, Chiba Prefecture";
   case 1241000: return "Yokoshibahikari Town, Chiba Prefecture";
   case 1242100: return "Ichinomiya Town, Chiba Prefecture";
   case 1242200: return "Mutsuzawa Town, Chiba Prefecture";
   case 1242300: return "Chosei Village, Chiba Prefecture";
   case 1242400: return "Shirako Town, Chiba Prefecture";
   case 1242600: return "Nagara, Chiba Prefecture";
   case 1242700: return "Chonancho, Chiba Prefecture";
   case 1244100: return "Otaki Town, Chiba Prefecture";
   case 1244300: return "Onjuku, Chiba Prefecture";
   case 1246300: return "Kyonan Town, Chiba Prefecture";
   case 1299999: return "Other municipalities in Chiba Prefecture";
   case 1310100: return "Chiyoda-ku, Tokyo";
   case 1310200: return "Chuo-ku, Tokyo";
   case 1310300: return "Minato-ku, Tokyo";
   case 1310400: return "Shinjuku, Tokyo";
   case 1310500: return "Bunkyo-ku, Tokyo";
   case 1310600: return "Taito Ward, Tokyo";
   case 1310700: return "Sumida Ward, Tokyo";
   case 1310800: return "Koto Ward, Tokyo";
   case 1310900: return "Shinagawa-ku, Tokyo";
   case 1311000: return "Meguro, Tokyo";
   case 1311100: return "Ota Ward, Tokyo";
   case 1311200: return "Setagaya, Tokyo";
   case 1311300: return "Shibuya, Tokyo";
   case 1311400: return "Nakano, Tokyo";
   case 1311500: return "Suginami-ku, Tokyo";
   case 1311600: return "Toshima-ku, Tokyo";
   case 1311700: return "Kita Ward, Tokyo";
   case 1311800: return "Arakawa-ku, Tokyo";
   case 1311900: return "Itabashi, Tokyo";
   case 1312000: return "Nerima, Tokyo";
   case 1312100: return "Adachi Ward, Tokyo";
   case 1312200: return "Katsushika Ward, Tokyo";
   case 1312300: return "Edogawa-ku, Tokyo";
   case 1320100: return "Hachioji, Tokyo";
   case 1320200: return "Tachikawa, Tokyo";
   case 1320300: return "Musashino, Tokyo";
   case 1320400: return "Mitaka, Tokyo";
   case 1320500: return "Ome City, Tokyo";
   case 1320600: return "Fuchu, Tokyo";
   case 1320700: return "Akishima, Tokyo";
   case 1320800: return "Chofu, Tokyo";
   case 1320900: return "Machida, Tokyo";
   case 1321000: return "Koganei, Tokyo";
   case 1321100: return "Kodaira, Tokyo";
   case 1321200: return "Hino, Tokyo";
   case 1321300: return "Higashimurayama, Tokyo";
   case 1321400: return "Kokubunji, Tokyo";
   case 1321500: return "Kunitachi, Tokyo";
   case 1321800: return "Fussa City, Tokyo";
   case 1321900: return "Komae, Tokyo";
   case 1322000: return "Higashiyamato, Tokyo";
   case 1322100: return "Kiyose, Tokyo";
   case 1322200: return "Higashikurume, Tokyo";
   case 1322300: return "Musashimurayama, Tokyo";
   case 1322400: return "Tama City, Tokyo";
   case 1322500: return "Inagi, Tokyo";
   case 1322700: return "Hamura, Tokyo";
   case 1322800: return "Akiruno, Tokyo";
   case 1322900: return "Nishitokyo City, Tokyo";
   case 1330300: return "Mizuho, Tokyo";
   case 1330500: return "Hinodecho, Tokyo";
   case 1330700: return "Hinohara Village, Tokyo";
   case 1330800: return "Okutama, Tokyo";
   case 1336100: return "Oshima, Tokyo";
   case 1336200: return "Toshima Village, Tokyo";
   case 1336300: return "Niijima Village, Tokyo";
   case 1336400: return "Kozushima, Tokyo";
   case 1338100: return "Miyake Village, Tokyo";
case 1338200: return "Mikurashima Village, Tokyo";
   case 1340000: return "Tokyo Hachijo Branch Office";
   case 1340100: return "Hachijocho, Tokyo";
   case 1340200: return "Aogashima Village, Tokyo";
   case 1342100: return "Ogasawara Village, Tokyo";
   case 1399999: return "Other municipalities in Tokyo";
   case 1410000: return "Yokohama City, Kanagawa Prefecture";
   case 1413000: return "Kawasaki, Kanagawa";
   case 1415000: return "Sagamihara City, Kanagawa Prefecture";
   case 1420100: return "Yokosuka City, Kanagawa Prefecture";
   case 1420300: return "Hiratsuka City, Kanagawa Prefecture";
   case 1420400: return "Kamakura City, Kanagawa Prefecture";
   case 1420500: return "Fujisawa City, Kanagawa Prefecture";
   case 1420600: return "Odawara City, Kanagawa Prefecture";
   case 1420700: return "Chigasaki City, Kanagawa Prefecture";
   case 1420800: return "Zushi City, Kanagawa Prefecture";
   case 1421000: return "Miura City, Kanagawa Prefecture";
   case 1421100: return "Hadano City, Kanagawa Prefecture";
   case 1421200: return "Atsugi City, Kanagawa Prefecture";
   case 1421300: return "Yamato City, Kanagawa Prefecture";
   case 1421400: return "Isehara City, Kanagawa Prefecture";
   case 1421500: return "Ebina City, Kanagawa Prefecture";
   case 1421600: return "Zama City, Kanagawa Prefecture";
   case 1421700: return "Minamiashigara City, Kanagawa Prefecture";
   case 1421800: return "Ayase City, Kanagawa Prefecture";
   case 1430100: return "Hayama Town, Kanagawa Prefecture";
   case 1432100: return "Kanagawa Samukawa";
   case 1434100: return "Oiso Town, Kanagawa Prefecture";
   case 1434200: return "Ninomiya, Kanagawa Prefecture";
   case 1436100: return "Nakaicho, Kanagawa Prefecture";
   case 1436200: return "Oimachi, Kanagawa Prefecture";
   case 1436300: return "Matsuda, Kanagawa Prefecture";
   case 1436400: return "Yamakita, Kanagawa Prefecture";
   case 1436600: return "Kaisei Town, Kanagawa Prefecture";
   case 1438200: return "Hakone, Kanagawa Prefecture";
   case 1438300: return "Manazuru, Kanagawa Prefecture";
   case 1438400: return "Yugawara, Kanagawa Prefecture";
   case 1440100: return "Aikawa, Kanagawa Prefecture";
   case 1440200: return "Kiyokawa Village, Kanagawa Prefecture";
   case 1499999: return "Other municipalities in Kanagawa Prefecture";
   case 1510000: return "Niigata City, Niigata Prefecture";
   case 1520200: return "Nagaoka City, Niigata Prefecture";
   case 1520400: return "Sanjo City, Niigata Prefecture";
   case 1520500: return "Kashiwazaki City, Niigata Prefecture";
   case 1520600: return "Shibata City, Niigata Prefecture";
   case 1520800: return "Ojiya City, Niigata Prefecture";
   case 1520900: return "Kamo City, Niigata Prefecture";
   case 1521000: return "Tokamachi City, Niigata Prefecture";
   case 1521100: return "Mitsuke City, Niigata Prefecture";
   case 1521200: return "Murakami City, Niigata Prefecture";
   case 1521300: return "Tsubame City, Niigata Prefecture";
   case 1521600: return "Itoigawa City, Niigata Prefecture";
case 1521700: return "Myoko City, Niigata Prefecture";
   case 1521800: return "Gosen City, Niigata Prefecture";
   case 1522200: return "Joetsu City, Niigata Prefecture";
   case 1522300: return "Agano City, Niigata Prefecture";
   case 1522400: return "Sado City, Niigata Prefecture";
   case 1522500: return "Uonuma City, Niigata Prefecture";
   case 1522600: return "Minamiuonuma City, Niigata Prefecture";
   case 1522700: return "Tanai City, Niigata Prefecture";
   case 1530700: return "Seiro Town, Niigata Prefecture";
   case 1534200: return "Yahiko Village, Niigata Prefecture";
   case 1536100: return "Takami Town, Niigata Prefecture";
   case 1538500: return "Aga Town, Niigata Prefecture";
   case 1540500: return "Izumozaki Town, Niigata Prefecture";
   case 1546100: return "Yuzawa Town, Niigata Prefecture";
   case 1548200: return "Tsunan Town, Niigata Prefecture";
   case 1550400: return "Kariwa Village, Niigata Prefecture";
   case 1558100: return "Sekikawa Village, Niigata Prefecture";
   case 1558600: return "Awashimaura Village, Niigata Prefecture";
   case 1599999: return "Other municipalities in Niigata Prefecture";
   case 1620100: return "Toyama City, Toyama Prefecture";
   case 1620200: return "Takaoka City, Toyama Prefecture";
   case 1620400: return "Uozu City, Toyama Prefecture";
   case 1620500: return "Himi City, Toyama Prefecture";
   case 1620600: return "Namerikawa City, Toyama Prefecture";
   case 1620700: return "Kurobe City, Toyama Prefecture";
   case 1620800: return "Tonami City, Toyama Prefecture";
   case 1620900: return "Oyabe City, Toyama Prefecture";
   case 1621000: return "Nanto City, Toyama Prefecture";
   case 1621100: return "Imizu City, Toyama Prefecture";
   case 1632100: return "Funahashi Village, Toyama Prefecture";
   case 1632200: return "Kamiichi Town, Toyama Prefecture";
   case 1632300: return "Tateyama Town, Toyama Prefecture";
   case 1634200: return "Nyuzen Town, Toyama Prefecture";
   case 1634300: return "Asahi Town, Toyama Prefecture";
   case 1699999: return "Other municipalities in Toyama Prefecture";
   case 1720100: return "Kanazawa City, Ishikawa Prefecture";
   case 1720200: return "Nanao City, Ishikawa Prefecture";
   case 1720300: return "Komatsu City, Ishikawa Prefecture";
   case 1720400: return "Wajima City, Ishikawa Prefecture";
   case 1720500: return "Suzu City, Ishikawa Prefecture";
   case 1720600: return "Kaga City, Ishikawa Prefecture";
   case 1720700: return "Hakui City, Ishikawa Prefecture";
   case 1720900: return "Kahoku City, Ishikawa Prefecture";
   case 1721000: return "Hakusan City, Ishikawa Prefecture";
   case 1721100: return "Nomi City, Ishikawa Prefecture";
   case 1721200: return "Nonoichi City, Ishikawa Prefecture";
   case 1732400: return "Kawakita Town, Ishikawa Prefecture";
   case 1736100: return "Tsubata, Ishikawa Prefecture";
   case 1736500: return "Uchinada Town, Ishikawa Prefecture";
   case 1738400: return "Shika Town, Ishikawa Prefecture";
   case 1738600: return "Houdatsushimizu Town, Ishikawa Prefecture";
   case 1740700: return "Nakanoto Town, Ishikawa Prefecture";
   case 1746100: return "Anamizu Town, Ishikawa Prefecture";
   case 1746300: return "Noto Town, Ishikawa Prefecture";
   case 1799999: return "Other municipalities in Ishikawa Prefecture";
   case 1820100: return "Fukui City, Fukui Prefecture";
   case 1820200: return "Tsuruga City, Fukui Prefecture";
   case 1820400: return "Obama City, Fukui Prefecture";
   case 1820500: return "Ono City, Fukui Prefecture";
   case 1820600: return "Katsuyama City, Fukui Prefecture";
   case 1820700: return "Sabae City, Fukui Prefecture";
   case 1820800: return "Awara City, Fukui Prefecture";
   case 1820900: return "Echizen City, Fukui Prefecture";
   case 1821000: return "Sakai City, Fukui Prefecture";
   case 1832200: return "Eiheiji Town, Fukui Prefecture";
   case 1838200: return "Ikeda Town, Fukui Prefecture";
   case 1840400: return "Minami Echizen Town, Fukui Prefecture";
   case 1842300: return "Echizen Town, Fukui Prefecture";
   case 1844200: return "Mihama Town, Fukui Prefecture";
   case 1848100: return "Takahama Town, Fukui Prefecture";
   case 1848300: return "Oi Town, Fukui Prefecture";
   case 1850100: return "Wakasa Town, Fukui Prefecture";
   case 1899999: return "Other municipalities in Fukui Prefecture";
   case 1920100: return "Kofu City, Yamanashi Prefecture";
   case 1920200: return "Fujiyoshida City, Yamanashi Prefecture";
   case 1920400: return "Tsuru City, Yamanashi Prefecture";
   case 1920500: return "Yamanashi City, Yamanashi Prefecture";
   case 1920600: return "Otsuki City, Yamanashi Prefecture";
   case 1920700: return "Nirasaki City, Yamanashi Prefecture";
case 1920800: return "Minami Alps City, Yamanashi Prefecture";
   case 1920900: return "Hokuto City, Yamanashi Prefecture";
   case 1921000: return "Kai City, Yamanashi Prefecture";
   case 1921100: return "Fuefuki City, Yamanashi Prefecture";
   case 1921200: return "Uenohara City, Yamanashi Prefecture";
   case 1921300: return "Koshu City, Yamanashi Prefecture";
   case 1921400: return "Chuo, Yamanashi";
   case 1934600: return "Ichikawamisato Town, Yamanashi Prefecture";
   case 1936400: return "Hayakawa Town, Yamanashi Prefecture";
   case 1936500: return "Minobu Town, Yamanashi Prefecture";
   case 1936600: return "Nanbu Town, Yamanashi Prefecture";
   case 1936800: return "Fujikawa Town, Yamanashi Prefecture";
   case 1938400: return "Showa Town, Yamanashi Prefecture";
   case 1942200: return "Doshi Village, Yamanashi Prefecture";
   case 1942300: return "Nishikatsura Town, Yamanashi Prefecture";
   case 1942400: return "Oshino Village, Yamanashi Prefecture";
   case 1942500: return "Yamanakako Village, Yamanashi Prefecture";
   case 1942900: return "Narusawa Village, Yamanashi Prefecture";
   case 1943000: return "Fujikawaguchiko Town, Yamanashi Prefecture";
   case 1944200: return "Kosuge Village, Yamanashi Prefecture";
   case 1944300: return "Tanba Yamamura, Yamanashi Prefecture";
   case 1999999: return "Other municipalities in Yamanashi Prefecture";
   case 2020100: return "Nagano City, Nagano Prefecture";
   case 2020200: return "Matsumoto City, Nagano Prefecture";
   case 2020300: return "Ueda City, Nagano Prefecture";
   case 2020400: return "Okaya City, Nagano Prefecture";
   case 2020500: return "Iida City, Nagano Prefecture";
   case 2020600: return "Suwa City, Nagano Prefecture";
   case 2020700: return "Suzaka City, Nagano Prefecture";
   case 2020800: return "Komoro City, Nagano Prefecture";
   case 2020900: return "Ina City, Nagano Prefecture";
   case 2021000: return "Komagane City, Nagano Prefecture";
   case 2021100: return "Nakano, Nagano";
   case 2021200: return "Omachi City, Nagano Prefecture";
   case 2021300: return "Iiyama, Nagano";
   case 2021400: return "Chino City, Nagano Prefecture";
   case 2021500: return "Shiojiri City, Nagano Prefecture";
   case 2021700: return "Saku City, Nagano Prefecture";
   case 2021800: return "Chikuma City, Nagano Prefecture";
   case 2021900: return "Tomi City, Nagano Prefecture";
   case 2022000: return "Azumino City, Nagano Prefecture";
   case 2030300: return "Koumi Town, Nagano Prefecture";
   case 2030400: return "Kawakami Village, Nagano Prefecture";
   case 2030500: return "Minamimaki Village, Nagano Prefecture";
   case 2030600: return "Minamiaiki Village, Nagano Prefecture";
   case 2030700: return "Kitaaiki Village, Nagano Prefecture";
   case 2030900: return "Sakuho Town, Nagano Prefecture";
   case 2032100: return "Karuizawa Town, Nagano Prefecture";
   case 2032300: return "Miyota Town, Nagano Prefecture";
   case 2032400: return "Tateshina Town, Nagano Prefecture";
   case 2034900: return "Aoki Village, Nagano Prefecture";
   case 2035000: return "Nagawa Town, Nagano Prefecture";
   case 2036100: return "Shimosuwa Town, Nagano Prefecture";
   case 2036200: return "Fujimi Town, Nagano Prefecture";
   case 2036300: return "Haramura, Nagano Prefecture";
   case 2038200: return "Tatsuno Town, Nagano Prefecture";
   case 2038300: return "Minowa Town, Nagano Prefecture";
   case 2038400: return "Iijima Town, Nagano Prefecture";
   case 2038500: return "Minamiminowa Village, Nagano Prefecture";
   case 2038600: return "Nakagawa, Nagano";
   case 2038800: return "Miyata Village, Nagano Prefecture";
   case 2040200: return "Matsukawa, Nagano";
   case 2040300: return "Takamori Town, Nagano Prefecture";
   case 2040400: return "Anan Town, Nagano Prefecture";
   case 2040700: return "Achi Village, Nagano Prefecture";
   case 2040900: return "Hiraya Village, Nagano Prefecture";
   case 2041000: return "Neba Village, Nagano Prefecture";
   case 2041100: return "Shimojo Village, Nagano Prefecture";
   case 2041200: return "Uriki Village, Nagano Prefecture";
   case 2041300: return "Tenryu Village, Nagano Prefecture";
   case 2041400: return "Taifu Village, Nagano Prefecture";
   case 2041500: return "Takagi Village, Nagano Prefecture";
   case 2041600: return "Toyooka Village, Nagano Prefecture";
   case 2041700: return "Oshika Village, Nagano Prefecture";
   case 2042200: return "Agematsu Town, Nagano Prefecture";
   case 2042300: return "Nagiso Town, Nagano Prefecture";
   case 2042500: return "Kiso Village, Nagano Prefecture";
   case 2042900: return "Otaki Village, Nagano Prefecture";
   case 2043000: return "Okuwa Village, Nagano Prefecture";
   case 2043200: return "Kiso Town, Nagano Prefecture";
   case 2044600: return "Maji Village, Nagano Prefecture";
   case 2044800: return "Ikusaka, Nagano";
   case 2045000: return "Yamagata Village, Nagano Prefecture";
   case 2045100: return "Asahi Village, Nagano Prefecture";
   case 2045200: return "Chikuhoku Village, Nagano Prefecture";
   case 2048100: return "Ikeda Town, Nagano Prefecture";
   case 2048200: return "Matsukawa Village, Nagano Prefecture";
   case 2048500: return "Hakuba Village, Nagano Prefecture";
   case 2048600: return "Otari Village, Nagano Prefecture";
   case 2052100: return "Sakaki Town, Nagano Prefecture";
   case 2054100: return "Obuse Town, Nagano Prefecture";
   case 2054300: return "Takayama Village, Nagano Prefecture";
   case 2056100: return "Yamanouchi Town, Nagano Prefecture";
   case 2056200: return "Kijimadaira Village, Nagano Prefecture";
   case 2056300: return "Nozawa Onsen Village, Nagano Prefecture";
   case 2058300: return "Shinanomachi, Nagano Prefecture";
   case 2058800: return "Ogawa Village, Nagano Prefecture";
   case 2059000: return "Iizuna Town, Nagano Prefecture";
   case 2060200: return "Sakae Village, Nagano Prefecture";
   case 2099999: return "Other municipalities in Nagano Prefecture";
   case 2120100: return "Gifu City, Gifu Prefecture";
   case 2120200: return "Ogaki City, Gifu Prefecture";
   case 2120300: return "Takayama City, Gifu Prefecture";
   case 2120400: return "Tajimi City, Gifu Prefecture";
   case 2120500: return "Seki City, Gifu Prefecture";
   case 2120600: return "Nakatsugawa City, Gifu Prefecture";
   case 2120700: return "Mino City, Gifu Prefecture";
   case 2120800: return "Mizunami City, Gifu Prefecture";
   case 2120900: return "Hashima City, Gifu Prefecture";
   case 2121000: return "Ena City, Gifu Prefecture";
   case 2121100: return "Minokamo City, Gifu Prefecture";
   case 2121200: return "Toki City, Gifu Prefecture";
   case 2121300: return "Kakamigahara City, Gifu Prefecture";
   case 2121400: return "Kani City, Gifu Prefecture";
   case 2121500: return "Yamagata City, Gifu Prefecture";
   case 2121600: return "Mizuho City, Gifu Prefecture";
   case 2121700: return "Hida City, Gifu Prefecture";
   case 2121800: return "Motosu City, Gifu Prefecture";
   case 2121900: return "Gujo City, Gifu Prefecture";
   case 2122000: return "Gero City, Gifu Prefecture";
   case 2122100: return "Kaizu City, Gifu Prefecture";
   case 2130200: return "Ginan Town, Gifu Prefecture";
   case 2130300: return "Kasamatsu, Gifu Prefecture";
   case 2134100: return "Yorocho, Gifu Prefecture";
   case 2136100: return "Tarui Town, Gifu Prefecture";
   case 2136200: return "Sekigahara Town, Gifu Prefecture";
   case 2138100: return "Kobe, Gifu Prefecture";
   case 2138200: return "Wanouchi Town, Gifu Prefecture";
   case 2138300: return "Anpachi, Gifu Prefecture";
   case 2140100: return "Ibigawa Town, Gifu Prefecture";
   case 2140300: return "Ono Town, Gifu Prefecture";
   case 2140400: return "Ikeda Town, Gifu Prefecture";
   case 2142100: return "Kitakata, Gifu Prefecture";
   case 2150100: return "Sakahogi, Gifu Prefecture";
   case 2150200: return "Tomika Town, Gifu Prefecture";
   case 2150300: return "Kawabe, Gifu Prefecture";
   case 2150400: return "Shichiso Town, Gifu Prefecture";
   case 2150500: return "Yaotsu Town, Gifu Prefecture";
   case 2150600: return "Shirakawa Town, Gifu Prefecture";
   case 2150700: return "Higashishirakawa Village, Gifu Prefecture";
   case 2152100: return "Mitake Town, Gifu Prefecture";
   case 2160400: return "Shirakawa Village, Gifu Prefecture";
   case 2199999: return "Other municipalities in Gifu Prefecture";
case 2210000: return "Shizuoka City, Shizuoka Prefecture";
   case 2213000: return "Hamamatsu City, Shizuoka Prefecture";
   case 2220300: return "Numazu City, Shizuoka Prefecture";
   case 2220500: return "Atami City, Shizuoka Prefecture";
   case 2220600: return "Mishima City, Shizuoka Prefecture";
   case 2220700: return "Fujinomiya City, Shizuoka Prefecture";
   case 2220800: return "Ito City, Shizuoka Prefecture";
   case 2220900: return "Shimada City, Shizuoka Prefecture";
   case 2221000: return "Fuji City, Shizuoka Prefecture";
   case 2221100: return "Iwata City, Shizuoka Prefecture";
   case 2221200: return "Yaizu City, Shizuoka Prefecture";
   case 2221300: return "Kakegawa City, Shizuoka Prefecture";
   case 2221400: return "Fujieda City, Shizuoka Prefecture";
   case 2221500: return "Gotemba City, Shizuoka Prefecture";
   case 2221600: return "Fukuroi City, Shizuoka Prefecture";
   case 2221900: return "Shimoda City, Shizuoka Prefecture";
   case 2222000: return "Susono City, Shizuoka Prefecture";
   case 2222100: return "Kosai City, Shizuoka Prefecture";
   case 2222200: return "Izu City, Shizuoka Prefecture";
   case 2222300: return "Omaezaki City, Shizuoka Prefecture";
   case 2222400: return "Kikugawa City, Shizuoka Prefecture";
   case 2222500: return "Izunokuni City, Shizuoka Prefecture";
   case 2222600: return "Makinohara City, Shizuoka Prefecture";
   case 2230100: return "Higashiizu Town, Shizuoka Prefecture";
   case 2230200: return "Kawazu, Shizuoka Prefecture";
   case 2230400: return "Minamiizu Town, Shizuoka Prefecture";
   case 2230500: return "Matsuzaki, Shizuoka Prefecture";
   case 2230600: return "Nishiizu, Shizuoka Prefecture";
   case 2232500: return "Kannami Town, Shizuoka Prefecture";
   case 2234100: return "Shimizu, Shizuoka Prefecture";
   case 2234200: return "Nagaizumi, Shizuoka Prefecture";
   case 2234400: return "Oyama Town, Shizuoka Prefecture";
   case 2242400: return "Yoshida, Shizuoka Prefecture";
   case 2242900: return "Kawanehon Town, Shizuoka Prefecture";
   case 2246100: return "Morimachi, Shizuoka Prefecture";
   case 2299999: return "Other municipalities in Shizuoka Prefecture";
   case 2310000: return "Nagoya, Aichi";
   case 2320100: return "Toyohashi, Aichi";
   case 2320200: return "Okazaki City, Aichi Prefecture";
   case 2320300: return "Ichinomiya City, Aichi Prefecture";
   case 2320400: return "Seto City, Aichi Prefecture";
   case 2320500: return "Handa City, Aichi Prefecture";
   case 2320600: return "Kasugai City, Aichi Prefecture";
   case 2320700: return "Toyokawa City, Aichi Prefecture";
   case 2320800: return "Tsushima City, Aichi Prefecture";
   case 2320900: return "Hekinan City, Aichi Prefecture";
   case 2321000: return "Kariya City, Aichi Prefecture";
   case 2321100: return "Toyota City, Aichi Prefecture";
   case 2321200: return "Anjo City, Aichi Prefecture";
   case 2321300: return "Nishio City, Aichi Prefecture";
   case 2321400: return "Gamagori City, Aichi Prefecture";
   case 2321500: return "Inuyama City, Aichi Prefecture";
   case 2321600: return "Tokoname City, Aichi Prefecture";
   case 2321700: return "Konan City, Aichi Prefecture";
   case 2321900: return "Komaki City, Aichi Prefecture";
   case 2322000: return "Inazawa, Aichi Prefecture";
   case 2322100: return "Shinshiro City, Aichi Prefecture";
   case 2322200: return "Tokai City, Aichi Prefecture";
   case 2322300: return "Obu City, Aichi Prefecture";
   case 2322400: return "Chita City, Aichi Prefecture";
   case 2322500: return "Chiryu City, Aichi Prefecture";
   case 2322600: return "Owariasahi City, Aichi Prefecture";
   case 2322700: return "Takahama City, Aichi Prefecture";
   case 2322800: return "Iwakura City, Aichi Prefecture";
   case 2322900: return "Toyoake City, Aichi Prefecture";
   case 2323000: return "Nisshin City, Aichi Prefecture";
   case 2323100: return "Tahara City, Aichi Prefecture";
   case 2323200: return "Aisai City, Aichi Prefecture";
   case 2323300: return "Kiyosu City, Aichi Prefecture";
   case 2323400: return "Kita-Nagoya City, Aichi Prefecture";
   case 2323500: return "Yatomi City, Aichi Prefecture";
   case 2323600: return "Miyoshi City, Aichi Prefecture";
   case 2323700: return "Ama City, Aichi Prefecture";
   case 2323800: return "Nagakute City, Aichi Prefecture";
   case 2330200: return "Togo Town, Aichi Prefecture";
   case 2334200: return "Toyoyama, Aichi Prefecture";
   case 2336100: return "Oguchi Town, Aichi Prefecture";
   case 2336200: return "Fuso Town, Aichi Prefecture";
   case 2342400: return "Oharu, Aichi";
   case 2342500: return "Kanie Town, Aichi Prefecture";
   case 2342700: return "Tobishima Village, Aichi Prefecture";
   case 2344100: return "Agui Town, Aichi Prefecture";
case 2344200: return "Higashiura Town, Aichi Prefecture";
   case 2344500: return "Minamichita Town, Aichi Prefecture";
   case 2344600: return "Mihama Town, Aichi Prefecture";
   case 2344700: return "Taketoyo, Aichi Prefecture";
   case 2350100: return "Kouda Town, Aichi Prefecture";
   case 2356100: return "Shitara Town, Aichi Prefecture";
   case 2356200: return "Toei Town, Aichi Prefecture";
   case 2356300: return "Toyone Village, Aichi Prefecture";
   case 2399999: return "Other municipalities in Aichi Prefecture";
   case 2420100: return "Tsu City, Mie Prefecture";
   case 2420200: return "Yokkaichi City, Mie Prefecture";
   case 2420300: return "Ise City, Mie Prefecture";
   case 2420400: return "Matsuzaka, Mie Prefecture";
   case 2420500: return "Kuwana City, Mie Prefecture";
   case 2420700: return "Suzuka City, Mie Prefecture";
   case 2420800: return "Nabari City, Mie Prefecture";
   case 2420900: return "Owase City, Mie Prefecture";
   case 2421000: return "Kameyama City, Mie Prefecture";
   case 2421100: return "Toba City, Mie Prefecture";
   case 2421200: return "Kumano City, Mie Prefecture";
   case 2421400: return "Inabe City, Mie Prefecture";
   case 2421500: return "Shima City, Mie Prefecture";
   case 2421600: return "Iga City, Mie Prefecture";
   case 2430300: return "Kisosaki Town, Mie Prefecture";
   case 2432400: return "Toin Town, Mie Prefecture";
   case 2434100: return "Komono Town, Mie Prefecture";
   case 2434300: return "Asahi Town, Mie Prefecture";
   case 2434400: return "Kawagoe, Mie Prefecture";
   case 2444100: return "Taki Town, Mie Prefecture";
   case 2444200: return "Meiwa Town, Mie Prefecture";
   case 2444300: return "Odai Town, Mie Prefecture";
   case 2446100: return "Tamaki Town, Mie Prefecture";
   case 2447000: return "Watakai Town, Mie Prefecture";
   case 2447100: return "Taiki Town, Mie Prefecture";
   case 2447200: return "Minamiise Town, Mie Prefecture";
   case 2454300: return "Kihoku, Mie Prefecture";
   case 2456100: return "Mihama Town, Mie Prefecture";
   case 2456200: return "Kiho Town, Mie Prefecture";
   case 2499999: return "Other municipalities in Mie prefecture";
   case 2520100: return "Otsu City, Shiga Prefecture";
   case 2520200: return "Hikone City, Shiga Prefecture";
   case 2520300: return "Nagahama City, Shiga Prefecture";
   case 2520400: return "Omihachiman City, Shiga Prefecture";
   case 2520600: return "Kusatsu City, Shiga Prefecture";
   case 2520700: return "Moriyama City, Shiga Prefecture";
   case 2520800: return "Ritto City, Shiga Prefecture";
   case 2520900: return "Koka City, Shiga Prefecture";
   case 2521000: return "Yasu City, Shiga Prefecture";
   case 2521100: return "Konan City, Shiga Prefecture";
   case 2521200: return "Takashima City, Shiga Prefecture";
   case 2521300: return "Higashiomi City, Shiga Prefecture";
   case 2521400: return "Maibara City, Shiga Prefecture";
   case 2538300: return "Hino Town, Shiga Prefecture";
   case 2538400: return "Ryuo Town, Shiga Prefecture";
   case 2542500: return "Aisho, Shiga Prefecture";
   case 2544100: return "Toyosato, Shiga Prefecture";
   case 2544200: return "Koura Town, Shiga Prefecture";
   case 2544300: return "Taga Town, Shiga Prefecture";
   case 2599999: return "Other municipalities in Shiga Prefecture";
   case 2610000: return "Kyoto City, Kyoto Prefecture";
   case 2620100: return "Fukuchiyama, Kyoto";
   case 2620200: return "Maizuru, Kyoto";
   case 2620300: return "Ayabe City, Kyoto Prefecture";
   case 2620400: return "Uji City, Kyoto Prefecture";
   case 2620500: return "Miyazu City, Kyoto Prefecture";
   case 2620600: return "Kameoka City, Kyoto Prefecture";
   case 2620700: return "Joyo City, Kyoto Prefecture";
   case 2620800: return "Muko City, Kyoto Prefecture";
   case 2620900: return "Nagaokakyo City, Kyoto Prefecture";
   case 2621000: return "Yawata City, Kyoto Prefecture";
   case 2621100: return "Kyotanabe, Kyoto";
   case 2621200: return "Kyotango, Kyoto";
   case 2621300: return "Nantan City, Kyoto Prefecture";
   case 2621400: return "Kizugawa City, Kyoto Prefecture";
   case 2630300: return "Oyamazaki Town, Kyoto Prefecture";
   case 2632200: return "Kumiyama Town, Kyoto Prefecture";
   case 2634300: return "Ide-cho, Kyoto";
   case 2634400: return "Ujitawara-cho, Kyoto";
   case 2636400: return "Kasagi Town, Kyoto Prefecture";
   case 2636500: return "Kyoto Wazuka";
   case 2636600: return "Seika, Kyoto";
   case 2636700: return "Minamiyamashiro Village, Kyoto Prefecture";
   case 2640700: return "Kyotanba-cho, Kyoto";
   case 2646300: return "Ine-cho, Kyoto";
   case 2646500: return "Yosano, Kyoto";
   case 2699999: return "Other municipalities in Kyoto Prefecture";
   case 2710000: return "Osaka City, Osaka Prefecture";
   case 2714000: return "Sakai, Osaka";
   case 2720200: return "Kishiwada, Osaka";
   case 2720300: return "Toyonaka, Osaka";
   case 2720400: return "Ikeda City, Osaka Prefecture";
   case 2720500: return "Suita, Osaka";
   case 2720600: return "Izumiotsu City, Osaka Prefecture";
   case 2720700: return "Takatsuki, Osaka";
   case 2720800: return "Kaizuka City, Osaka Prefecture";
   case 2720900: return "Moriguchi, Osaka";
   case 2721000: return "Hirakata, Osaka";
   case 2721100: return "Ibaraki, Osaka";
   case 2721200: return "Yao City, Osaka Prefecture";
   case 2721300: return "Izumisano, Osaka";
   case 2721400: return "Tondabayashi, Osaka";
   case 2721500: return "Neyagawa, Osaka";
   case 2721600: return "Kawachinagano, Osaka";
   case 2721700: return "Matsubara, Osaka";
   case 2721800: return "Daito City, Osaka Prefecture";
   case 2721900: return "Izumi City, Osaka Prefecture";
   case 2722000: return "Minoh City, Osaka Prefecture";
   case 2722100: return "Kashiwara City, Osaka Prefecture";
case 2722200: return "Habikino City, Osaka Prefecture";
   case 2722300: return "Kadoma City, Osaka Prefecture";
   case 2722400: return "Settsu City, Osaka Prefecture";
   case 2722500: return "Takaishi, Osaka";
   case 2722600: return "Fujiidera, Osaka";
   case 2722700: return "Higashi Osaka City, Osaka Prefecture";
   case 2722800: return "Sennan, Osaka";
   case 2722900: return "Shijonawate City, Osaka Prefecture";
   case 2723000: return "Katano City, Osaka Prefecture";
   case 2723100: return "Osaka Sayama City, Osaka Prefecture";
   case 2723200: return "Hannan City, Osaka Prefecture";
   case 2730100: return "Shimamoto Town, Osaka Prefecture";
   case 2732100: return "Toyonocho, Osaka";
   case 2732200: return "Nose Town, Osaka Prefecture";
   case 2734100: return "Tadaokacho, Osaka";
   case 2736100: return "Kumatori, Osaka";
   case 2736200: return "Tajiri, Osaka";
   case 2736600: return "Misakicho, Osaka";
   case 2738100: return "Taishicho, Osaka";
   case 2738200: return "Kanancho, Osaka";
   case 2738300: return "Chihaya Akasaka Village, Osaka Prefecture";
   case 2799999: return "Other municipalities in Osaka Prefecture";
   case 2810000: return "Kobe City, Hyogo Prefecture";
   case 2820100: return "Himeji City, Hyogo Prefecture";
   case 2820200: return "Amagasaki City, Hyogo Prefecture";
   case 2820300: return "Akashi City, Hyogo Prefecture";
   case 2820400: return "Nishinomiya City, Hyogo Prefecture";
   case 2820500: return "Sumoto City, Hyogo Prefecture";
   case 2820600: return "Ashiya City, Hyogo Prefecture";
   case 2820700: return "Itami City, Hyogo Prefecture";
   case 2820800: return "Aioi City, Hyogo Prefecture";
   case 2820900: return "Toyooka City, Hyogo Prefecture";
   case 2821000: return "Kakogawa City, Hyogo Prefecture";
   case 2821200: return "Ako City, Hyogo Prefecture";
   case 2821300: return "Nishiwaki City, Hyogo Prefecture";
   case 2821400: return "Takarazuka City, Hyogo Prefecture";
   case 2821500: return "Miki City, Hyogo Prefecture";
   case 2821600: return "Takasago City, Hyogo Prefecture";
   case 2821700: return "Kawanishi City, Hyogo Prefecture";
   case 2821800: return "Ono City, Hyogo Prefecture";
   case 2821900: return "Sanda City, Hyogo Prefecture";
   case 2822000: return "Kasai City, Hyogo Prefecture";
   case 2822100: return "Tanba Sasayama City, Hyogo Prefecture";
   case 2822200: return "Yabu City, Hyogo Prefecture";
   case 2822300: return "Tamba City, Hyogo Prefecture";
   case 2822400: return "Minamiawaji City, Hyogo Prefecture";
   case 2822500: return "Asago City, Hyogo Prefecture";
   case 2822600: return "Awaji City, Hyogo Prefecture";
   case 2822700: return "Shiso City, Hyogo Prefecture";
   case 2822800: return "Kato City, Hyogo Prefecture";
   case 2822900: return "Tatsuno City, Hyogo Prefecture";
   case 2830100: return "Inagawa Town, Hyogo Prefecture";
   case 2836500: return "Taka Town, Hyogo Prefecture";
   case 2838100: return "Inami Town, Hyogo Prefecture";
   case 2838200: return "Harima Town, Hyogo Prefecture";
   case 2844200: return "Ichikawa Town, Hyogo Prefecture";
   case 2844300: return "Fukusaki, Hyogo Prefecture";
   case 2844600: return "Kamikawa, Hyogo Prefecture";
   case 2846400: return "Taishi Town, Hyogo Prefecture";
   case 2848100: return "Kamigori Town, Hyogo Prefecture";
   case 2850100: return "Sayo Town, Hyogo Prefecture";
   case 2858500: return "Kami Town, Hyogo Prefecture";
   case 2858600: return "Shin Onsen Town, Hyogo Prefecture";
   case 2899999: return "Other municipalities in Hyogo Prefecture";
   case 2920100: return "Nara City, Nara Prefecture";
   case 2920200: return "Yamatotakada City, Nara Prefecture";
   case 2920300: return "Yamatokoriyama City, Nara Prefecture";
   case 2920400: return "Tenri City, Nara Prefecture";
   case 2920500: return "Kashihara, Nara Prefecture";
   case 2920600: return "Sakurai City, Nara Prefecture";
   case 2920700: return "Gojo City, Nara Prefecture";
   case 2920800: return "Gose City, Nara Prefecture";
   case 2920900: return "Ikoma City, Nara Prefecture";
   case 2921000: return "Kashiba City, Nara Prefecture";
   case 2921100: return "Katsuragi City, Nara Prefecture";
   case 2921200: return "Uda City, Nara Prefecture";
   case 2932200: return "Yamazoe Village, Nara Prefecture";
   case 2934200: return "Hegun Town, Nara Prefecture";
   case 2934300: return "Misato Town, Nara Prefecture";
   case 2934400: return "Ikaruga, Nara Prefecture";
   case 2934500: return "Anto Town, Nara Prefecture";
   case 2936100: return "Kawanishi Town, Nara Prefecture";
   case 2936200: return "Miyake, Nara Prefecture";
   case 2936300: return "Tawaramoto Town, Nara Prefecture";
   case 2938500: return "Soni Village, Nara Prefecture";
   case 2938600: return "Mitsue Village, Nara Prefecture";
   case 2940100: return "Takatori Town, Nara Prefecture";
   case 2940200: return "Asuka Village, Nara Prefecture";
   case 2942400: return "Kamimaki Town, Nara Prefecture";
   case 2942500: return "Oji Town, Nara Prefecture";
   case 2942600: return "Koryo Town, Nara Prefecture";
   case 2942700: return "Kawai Town, Nara Prefecture";
   case 2944100: return "Yoshino, Nara";
   case 2944200: return "Oyodo Town, Nara Prefecture";
   case 2944300: return "Shimoichi Town, Nara Prefecture";
   case 2944400: return "Kurotaki Village, Nara Prefecture";
   case 2944600: return "Tenkawa Village, Nara Prefecture";
   case 2944700: return "Nosakogawa Village, Nara Prefecture";
   case 2944900: return "Totsukawa, Nara Prefecture";
   case 2945000: return "Shimokitayama Village, Nara Prefecture";
   case 2945100: return "Kamikitayama Village, Nara Prefecture";
   case 2945200: return "Kawakami Village, Nara Prefecture";
   case 2945300: return "Higashiyoshino Village, Nara Prefecture";
   case 2999999: return "Other municipalities in Nara Prefecture";
case 3020100: return "Wakayama City, Wakayama Prefecture";
   case 3020200: return "Kainan City, Wakayama Prefecture";
   case 3020300: return "Hashimoto City, Wakayama Prefecture";
   case 3020400: return "Arita City, Wakayama Prefecture";
   case 3020500: return "Gobo City, Wakayama Prefecture";
   case 3020600: return "Tanabe, Wakayama";
   case 3020700: return "Shingu City, Wakayama Prefecture";
   case 3020800: return "Kinokawa City, Wakayama Prefecture";
   case 3020900: return "Iwade City, Wakayama Prefecture";
   case 3030400: return "Kimino Town, Wakayama Prefecture";
   case 3034100: return "Katsuragi Town, Wakayama Prefecture";
   case 3034300: return "Kudoyama Town, Wakayama Prefecture";
   case 3034400: return "Koya Town, Wakayama Prefecture";
   case 3036100: return "Yuasa, Wakayama Prefecture";
   case 3036200: return "Hirogawa Town, Wakayama Prefecture";
   case 3036600: return "Aritagawa Town, Wakayama Prefecture";
   case 3038100: return "Mihama, Wakayama Prefecture";
   case 3038200: return "Hidaka Town, Wakayama Prefecture";
   case 3038300: return "Yura Town, Wakayama Prefecture";
   case 3039000: return "Inami Town, Wakayama Prefecture";
   case 3039100: return "Minabe Town, Wakayama Prefecture";
   case 3039200: return "Hidakagawa Town, Wakayama Prefecture";
   case 3040100: return "Shirahama, Wakayama Prefecture";
   case 3040400: return "Kamitonda, Wakayama Prefecture";
   case 3040600: return "Susami Town, Wakayama Prefecture";
   case 3042100: return "Nachikatsuura Town, Wakayama Prefecture";
   case 3042200: return "Taiji, Wakayama Prefecture";
   case 3042400: return "Kozagawa Town, Wakayama Prefecture";
   case 3042700: return "Kitayama Village, Wakayama Prefecture";
   case 3042800: return "Kushimoto, Wakayama Prefecture";
   case 3099999: return "Other municipalities in Wakayama Prefecture";
   case 3120100: return "Tottori City, Tottori Prefecture";
   case 3120200: return "Yonago City, Tottori Prefecture";
   case 3120300: return "Kurayoshi City, Tottori Prefecture";
   case 3120400: return "Sakaiminato City, Tottori Prefecture";
   case 3130200: return "Iwami Town, Tottori Prefecture";
   case 3132500: return "Wakasa Town, Tottori Prefecture";
   case 3132800: return "Chizu Town, Tottori Prefecture";
   case 3132900: return "Yazucho, Tottori Prefecture";
   case 3136400: return "Misasa Town, Tottori Prefecture";
   case 3137000: return "Yurihama Town, Tottori Prefecture";
   case 3137100: return "Kotoura Town, Tottori Prefecture";
   case 3137200: return "Hokuei Town, Tottori Prefecture";
   case 3138400: return "Hiezu Village, Tottori Prefecture";
   case 3138600: return "Oyama Town, Tottori Prefecture";
   case 3138900: return "Nanbu Town, Tottori Prefecture";
   case 3139000: return "Hoki Town, Tottori Prefecture";
   case 3140100: return "Nichinan Town, Tottori Prefecture";
   case 3140200: return "Hino Town, Tottori Prefecture";
   case 3140300: return "Kofu Town, Tottori Prefecture";
   case 3199999: return "Other municipalities in Tottori Prefecture";
   case 3220100: return "Matsue City, Shimane Prefecture";
   case 3220200: return "Hamada City, Shimane Prefecture";
   case 3220300: return "Izumo City, Shimane Prefecture";
   case 3220400: return "Masuda City, Shimane Prefecture";
   case 3220500: return "Ota City, Shimane Prefecture";
   case 3220600: return "Yasugi City, Shimane Prefecture";
   case 3220700: return "Gotsu City, Shimane Prefecture";
   case 3220900: return "Unnan City, Shimane Prefecture";
   case 3234300: return "Okuizumo Town, Shimane Prefecture";
   case 3238600: return "Iinan Town, Shimane Prefecture";
   case 3244100: return "Kawamoto Town, Shimane Prefecture";
   case 3244800: return "Misato Town, Shimane Prefecture";
   case 3244900: return "Onan Town, Shimane Prefecture";
   case 3250100: return "Tsuwano Town, Shimane Prefecture";
   case 3250500: return "Yoshika Town, Shimane Prefecture";
   case 3252500: return "Ama Town, Shimane Prefecture";
   case 3252600: return "Nishinoshima Town, Shimane Prefecture";
   case 3252700: return "Chio Village, Shimane Prefecture";
   case 3252800: return "Okinoshima Town, Shimane Prefecture";
   case 3299999: return "Other municipalities in Shimane Prefecture";
   case 3310000: return "Okayama City, Okayama Prefecture";
   case 3320200: return "Kurashiki City, Okayama Prefecture";
   case 3320300: return "Tsuyama City, Okayama Prefecture";
   case 3320400: return "Tamano City, Okayama Prefecture";
   case 3320500: return "Kasaoka City, Okayama Prefecture";
   case 3320700: return "Ibara City, Okayama Prefecture";
   case 3320800: return "Soja City, Okayama Prefecture";
   case 3320900: return "Takahashi City, Okayama Prefecture";
   case 3321000: return "Niimi City, Okayama Prefecture";
   case 3321100: return "Bizen City, Okayama Prefecture";
   case 3321200: return "Setouchi City, Okayama Prefecture";
   case 3321300: return "Akaiwa City, Okayama Prefecture";
   case 3321400: return "Maniwa City, Okayama Prefecture";
   case 3321500: return "Mimasaka City, Okayama Prefecture";
   case 3321600: return "Asakuchi City, Okayama Prefecture";
   case 3334600: return "Wake Town, Okayama Prefecture";
   case 3342300: return "Hayashima Town, Okayama Prefecture";
   case 3344500: return "Satocho, Okayama Prefecture";
   case 3346100: return "Yakage, Okayama Prefecture";
   case 3358600: return "Shinjo Village, Okayama Prefecture";
   case 3360600: return "Kagamino Town, Okayama Prefecture";
   case 3362200: return "Katsuo Town, Okayama Prefecture";
   case 3362300: return "Nagi Town, Okayama Prefecture";
   case 3364300: return "Nishiawakura Village, Okayama Prefecture";
   case 3366300: return "Kumenan Town, Okayama Prefecture";
   case 3366600: return "Misaki Town, Okayama Prefecture";
   case 3368100: return "Kibichuo Town, Okayama Prefecture";
   case 3399999: return "Okayama other municipalities";
   case 3410000: return "Hiroshima City, Hiroshima Prefecture";
   case 3420200: return "Kure City, Hiroshima Prefecture";
   case 3420300: return "Takehara City, Hiroshima Prefecture";
   case 3420400: return "Mihara City, Hiroshima Prefecture";
   case 3420500: return "Onomichi City, Hiroshima Prefecture";
   case 3420700: return "Fukuyama City, Hiroshima Prefecture";
   case 3420800: return "Fuchu City, Hiroshima Prefecture";
   case 3420900: return "Miyoshi City, Hiroshima Prefecture";
case 3421000: return "Shobara City, Hiroshima Prefecture";
   case 3421100: return "Otake City, Hiroshima Prefecture";
   case 3421200: return "Higashi Hiroshima City, Hiroshima Prefecture";
   case 3421300: return "Hatsukaichi City, Hiroshima Prefecture";
   case 3421400: return "Akitakata City, Hiroshima Prefecture";
   case 3421500: return "Etajima City, Hiroshima Prefecture";
   case 3430200: return "Fuchu Town, Hiroshima Prefecture";
   case 3430400: return "Kaita Town, Hiroshima Prefecture";
   case 3430700: return "Kumano Town, Hiroshima Prefecture";
   case 3430900: return "Saka Town, Hiroshima Prefecture";
   case 3436800: return "Akiota Town, Hiroshima Prefecture";
   case 3436900: return "Kitahiroshima Town, Hiroshima Prefecture";
   case 3443100: return "Osakikamijima Town, Hiroshima Prefecture";
   case 3446200: return "Sera Town, Hiroshima Prefecture";
   case 3454500: return "Jinseki Kogen Town, Hiroshima Prefecture";
   case 3499999: return "Other municipalities in Hiroshima Prefecture";
   case 3520100: return "Shimonoseki City, Yamaguchi Prefecture";
   case 3520200: return "Ube City, Yamaguchi Prefecture";
   case 3520300: return "Yamaguchi City, Yamaguchi Prefecture";
   case 3520400: return "Hagi City, Yamaguchi Prefecture";
   case 3520600: return "Hofu City, Yamaguchi Prefecture";
   case 3520700: return "Kudamatsu City, Yamaguchi Prefecture";
   case 3520800: return "Iwakuni City, Yamaguchi Prefecture";
   case 3521000: return "Hikari City, Yamaguchi Prefecture";
   case 3521100: return "Nagato City, Yamaguchi Prefecture";
   case 3521200: return "Yanai City, Yamaguchi Prefecture";
   case 3521300: return "Mine City, Yamaguchi Prefecture";
   case 3521500: return "Shunan City, Yamaguchi Prefecture";
   case 3521600: return "Sanyo Onoda City, Yamaguchi Prefecture";
   case 3530500: return "Suo Oshima Town, Yamaguchi Prefecture";
   case 3532100: return "Waki, Yamaguchi";
   case 3534100: return "Kaminoseki, Yamaguchi Prefecture";
   case 3534300: return "Tabuse Town, Yamaguchi Prefecture";
   case 3534400: return "Yamaguchi Hirao Town";
   case 3550200: return "Abu Town, Yamaguchi Prefecture";
   case 3599999: return "Other municipalities in Yamaguchi Prefecture";
   case 3620100: return "Tokushima City, Tokushima Prefecture";
   case 3620200: return "Naruto City, Tokushima Prefecture";
   case 3620300: return "Komatsushima City, Tokushima Prefecture";
   case 3620400: return "Anan City, Tokushima Prefecture";
   case 3620500: return "Yoshinogawa City, Tokushima Prefecture";
   case 3620600: return "Awa City, Tokushima Prefecture";
   case 3620700: return "Mima City, Tokushima Prefecture";
   case 3620800: return "Miyoshi City, Tokushima Prefecture";
   case 3630100: return "Katsuura Town, Tokushima Prefecture";
   case 3630200: return "Kamikatsu Town, Tokushima Prefecture";
   case 3632100: return "Sanagouchi Village, Tokushima Prefecture";
   case 3634100: return "Ishii Town, Tokushima Prefecture";
   case 3634200: return "Kamiyama Town, Tokushima Prefecture";
   case 3636800: return "Naga Town, Tokushima Prefecture";
   case 3638300: return "Mugi Town, Tokushima Prefecture";
   case 3638700: return "Minami Town, Tokushima Prefecture";
   case 3638800: return "Kaiyo Town, Tokushima Prefecture";
   case 3640100: return "Matsushige Town, Tokushima Prefecture";
   case 3640200: return "Kitajima Town, Tokushima Prefecture";
   case 3640300: return "Aizumi Town, Tokushima Prefecture";
   case 3640400: return "Itano Town, Tokushima Prefecture";
   case 3640500: return "Kamiita Town, Tokushima Prefecture";
   case 3646800: return "Tsurugi Town, Tokushima Prefecture";
   case 3648900: return "Higashimiyoshi Town, Tokushima Prefecture";
   case 3699999: return "Other municipalities in Tokushima Prefecture";
   case 3720100: return "Takamatsu City, Kagawa Prefecture";
   case 3720200: return "Marugame City, Kagawa Prefecture";
   case 3720300: return "Sakaide City, Kagawa Prefecture";
   case 3720400: return "Zentsuji City, Kagawa Prefecture";
   case 3720500: return "Kannonji City, Kagawa Prefecture";
   case 3720600: return "Sanuki City, Kagawa Prefecture";
   case 3720700: return "Higashikagawa City, Kagawa Prefecture";
   case 3720800: return "Mitoyo City, Kagawa Prefecture";
   case 3732200: return "Tonosho, Kagawa Prefecture";
   case 3732400: return "Shodoshima Town, Kagawa Prefecture";
   case 3734100: return "Mikicho, Kagawa Prefecture";
   case 3736400: return "Naoshima, Kagawa Prefecture";
   case 3738600: return "Utazu Town, Kagawa Prefecture";
   case 3738700: return "Ayagawa Town, Kagawa Prefecture";
   case 3740300: return "Kotohira, Kagawa Prefecture";
   case 3740400: return "Tadotsu Town, Kagawa Prefecture";
   case 3740600: return "Mannou Town, Kagawa Prefecture";
   case 3799999: return "Other municipalities in Kagawa prefecture";
   case 3820100: return "Matsuyama City, Ehime Prefecture";
   case 3820200: return "Imabari City, Ehime Prefecture";
   case 3820300: return "Uwajima City, Ehime Prefecture";
   case 3820400: return "Yawatahama City, Ehime Prefecture";
   case 3820500: return "Niihama City, Ehime Prefecture";
   case 3820600: return "Saijo City, Ehime Prefecture";
   case 3820700: return "Ozu City, Ehime Prefecture";
   case 3821000: return "Iyo City, Ehime Prefecture";
   case 3821300: return "Shikokuchuo City, Ehime Prefecture";
   case 3821400: return "Seiyo City, Ehime Prefecture";
   case 3821500: return "Toon City, Ehime Prefecture";
   case 3835600: return "Kamijima Town, Ehime Prefecture";
   case 3838600: return "Ehime Prefecture Kumakogen Town";
   case 3840100: return "Matsumae, Ehime Prefecture";
   case 3840200: return "Tobe Town, Ehime Prefecture";
   case 3842200: return "Uchiko Town, Ehime Prefecture";
   case 3844200: return "Ikata Town, Ehime Prefecture";
   case 3848400: return "Matsuno Town, Ehime Prefecture";
   case 3848800: return "Kihoku, Ehime Prefecture";
   case 3850600: return "Ainan Town, Ehime Prefecture";
   case 3899999: return "Other municipalities in Ehime Prefecture";
   case 3920100: return "Kochi City, Kochi Prefecture";
   case 3920200: return "Muroto City, Kochi Prefecture";
   case 3920300: return "Aki City, Kochi Prefecture";
   case 3920400: return "Nankoku City, Kochi Prefecture";
   case 3920500: return "Tosa City, Kochi Prefecture";
   case 3920600: return "Susaki City, Kochi Prefecture";
   case 3920800: return "Sukumo City, Kochi Prefecture";
   case 3920900: return "Tosashimizu City, Kochi Prefecture";
   case 3921000: return "Shimanto City, Kochi Prefecture";
case 3921100: return "Konan City, Kochi Prefecture";
   case 3921200: return "Kami City, Kochi Prefecture";
   case 3930100: return "Toyocho, Kochi Prefecture";
   case 3930200: return "Nahari Town, Kochi Prefecture";
   case 3930300: return "Tano Town, Kochi Prefecture";
   case 3930400: return "Yasuda Town, Kochi Prefecture";
   case 3930500: return "Kitagawa Village, Kochi Prefecture";
   case 3930600: return "Umaji Village, Kochi Prefecture";
   case 3930700: return "Geisei Village, Kochi Prefecture";
   case 3934100: return "Motoyama Town, Kochi Prefecture";
   case 3934400: return "Otoyo Town, Kochi Prefecture";
   case 3936300: return "Tosa Town, Kochi Prefecture";
   case 3936400: return "Okawa Village, Kochi Prefecture";
   case 3938600: return "Ino Town, Kochi Prefecture";
   case 3938700: return "Niyodogawa Town, Kochi Prefecture";
   case 3940100: return "Nakatosa Town, Kochi Prefecture";
   case 3940200: return "Sagawa Town, Kochi Prefecture";
   case 3940300: return "Ochi Town, Kochi Prefecture";
   case 3940500: return "Yuyuhara Town, Kochi Prefecture";
   case 3941000: return "Hidaka Village, Kochi Prefecture";
   case 3941100: return "Tsuno Town, Kochi Prefecture";
   case 3941200: return "Shimanto Town, Kochi Prefecture";
   case 3942400: return "Otsuki Town, Kochi Prefecture";
   case 3942700: return "Mihara Village, Kochi Prefecture";
   case 3942800: return "Kuroshio Town, Kochi Prefecture";
   case 3999999: return "Other municipalities in Kochi Prefecture";
   case 4010000: return "Kitakyushu City, Fukuoka Prefecture";
   case 4013000: return "Fukuoka City, Fukuoka Prefecture";
   case 4020200: return "Omuta City, Fukuoka Prefecture";
   case 4020300: return "Kurume City, Fukuoka Prefecture";
   case 4020400: return "Nogata City, Fukuoka Prefecture";
   case 4020500: return "Iizuka City, Fukuoka Prefecture";
   case 4020600: return "Tagawa City, Fukuoka Prefecture";
   case 4020700: return "Yanagawa City, Fukuoka Prefecture";
   case 4021000: return "Yame City, Fukuoka Prefecture";
   case 4021100: return "Chikugo City, Fukuoka Prefecture";
   case 4021200: return "Okawa City, Fukuoka Prefecture";
   case 4021300: return "Yukuhashi, Fukuoka";
   case 4021400: return "Buzen City, Fukuoka Prefecture";
   case 4021500: return "Nakama City, Fukuoka Prefecture";
   case 4021600: return "Ogori City, Fukuoka Prefecture";
   case 4021700: return "Chikushino City, Fukuoka Prefecture";
   case 4021800: return "Kasuga City, Fukuoka Prefecture";
   case 4021900: return "Onojo City, Fukuoka Prefecture";
   case 4022000: return "Munakata City, Fukuoka Prefecture";
   case 4022100: return "Dazaifu City, Fukuoka Prefecture";
   case 4022300: return "Koga City, Fukuoka Prefecture";
   case 4022400: return "Fukutsu City, Fukuoka Prefecture";
   case 4022500: return "Ukiha City, Fukuoka Prefecture";
   case 4022600: return "Miyawaka, Fukuoka";
   case 4022700: return "Kama City, Fukuoka Prefecture";
   case 4022800: return "Asakura City, Fukuoka Prefecture";
   case 4022900: return "Miyama City, Fukuoka Prefecture";
   case 4023000: return "Itoshima City, Fukuoka Prefecture";
   case 4023100: return "Nakagawa City, Fukuoka Prefecture";
   case 4034100: return "Umi Town, Fukuoka Prefecture";
   case 4034200: return "Sasaguri Town, Fukuoka Prefecture";
   case 4034300: return "Shime Town, Fukuoka Prefecture";
   case 4034400: return "Sue Town, Fukuoka Prefecture";
   case 4034500: return "Shingu Town, Fukuoka Prefecture";
   case 4034800: return "Hisayama, Fukuoka Prefecture";
   case 4034900: return "Kasuya Town, Fukuoka Prefecture";
   case 4038100: return "Ashiya, Fukuoka Prefecture";
   case 4038200: return "Mizumaki Town, Fukuoka Prefecture";
   case 4038300: return "Okagaki Town, Fukuoka Prefecture";
   case 4038400: return "Onga Town, Fukuoka Prefecture";
   case 4040100: return "Kotake Town, Fukuoka Prefecture";
   case 4040200: return "Kurate Town, Fukuoka Prefecture";
   case 4042100: return "Katsuragawa Town, Fukuoka Prefecture";
   case 4044700: return "Chikuzen Town, Fukuoka Prefecture";
   case 4044800: return "Toho Village, Fukuoka Prefecture";
   case 4050300: return "Tachiarai Town, Fukuoka Prefecture";
   case 4052200: return "Oki Town, Fukuoka Prefecture";
   case 4054400: return "Hirogawa Town, Fukuoka Prefecture";
   case 4060100: return "Koharu Town, Fukuoka Prefecture";
   case 4060200: return "Soeda Town, Fukuoka Prefecture";
   case 4060400: return "Itoda Town, Fukuoka Prefecture";
   case 4060500: return "Kawasaki Town, Fukuoka Prefecture";
   case 4060800: return "Oto Town, Fukuoka Prefecture";
   case 4060900: return "Akamura, Fukuoka Prefecture";
   case 4061000: return "Fukuchi Town, Fukuoka Prefecture";
   case 4062100: return "Kanda Town, Fukuoka Prefecture";
   case 4062500: return "Miyako Town, Fukuoka Prefecture";
   case 4064200: return "Yoshitomi Town, Fukuoka Prefecture";
   case 4064600: return "Jomo Town, Fukuoka Prefecture";
   case 4064700: return "Chikujo, Fukuoka Prefecture";
   case 4099999: return "Other municipalities in Fukuoka Prefecture";
   case 4120100: return "Saga City, Saga Prefecture";
   case 4120200: return "Karatsu City, Saga Prefecture";
   case 4120300: return "Tosu City, Saga Prefecture";
   case 4120400: return "Taku City, Saga Prefecture";
   case 4120500: return "Imari City, Saga Prefecture";
   case 4120600: return "Takeo City, Saga Prefecture";
   case 4120700: return "Kashima City, Saga Prefecture";
   case 4120800: return "Ogi City, Saga Prefecture";
   case 4120900: return "Ureshino City, Saga Prefecture";
   case 4121000: return "Kanzaki City, Saga Prefecture";
   case 4132700: return "Yoshinogari Town, Saga Prefecture";
   case 4134100: return "Kiyama Town, Saga Prefecture";
   case 4134500: return "Kamimine Town, Saga Prefecture";
   case 4134600: return "Miyaki Town, Saga Prefecture";
   case 4138700: return "Genkai Town, Saga Prefecture";
   case 4140100: return "Arita Town, Saga Prefecture";
   case 4142300: return "Omachi Town, Saga Prefecture";
   case 4142400: return "Kohoku Town, Saga Prefecture";
   case 4142500: return "Shiroishi Town, Saga Prefecture";
   case 4144100: return "Tara Town, Saga Prefecture";
   case 4199999: return "Other municipalities in Saga Prefecture";
   case 4220100: return "Nagasaki City, Nagasaki Prefecture";
   case 4220200: return "Sasebo City, Nagasaki Prefecture";
   case 4220300: return "Shimabara City, Nagasaki Prefecture";
   case 4220400: return "Isahaya, Nagasaki Prefecture";
   case 4220500: return "Omura City, Nagasaki Prefecture";
   case 4220700: return "Hirado City, Nagasaki Prefecture";
   case 4220800: return "Matsuura City, Nagasaki Prefecture";
   case 4220900: return "Tsushima, Nagasaki Prefecture";
   case 4221000: return "Iki City, Nagasaki Prefecture";
   case 4221100: return "Goto City, Nagasaki Prefecture";
   case 4221200: return "Saikai City, Nagasaki Prefecture";
   case 4221300: return "Unzen City, Nagasaki Prefecture";
case 4221400: return "Minamishimabara City, Nagasaki Prefecture";
   case 4230700: return "Nagayo Town, Nagasaki Prefecture";
   case 4230800: return "Tokitsu Town, Nagasaki Prefecture";
   case 4232100: return "Higashisonogi Town, Nagasaki Prefecture";
   case 4232200: return "Kawatana Town, Nagasaki Prefecture";
   case 4232300: return "Hasami Town, Nagasaki Prefecture";
   case 4238300: return "Ojika Town, Nagasaki Prefecture";
   case 4239100: return "Saza Town, Nagasaki Prefecture";
   case 4241100: return "Shinkamigoto Town, Nagasaki Prefecture";
   case 4299999: return "Other municipalities in Nagasaki Prefecture";
   case 4310000: return "Kumamoto City, Kumamoto Prefecture";
   case 4320200: return "Yatsushiro City, Kumamoto Prefecture";
   case 4320300: return "Hitoyoshi City, Kumamoto Prefecture";
   case 4320400: return "Arao City, Kumamoto Prefecture";
   case 4320500: return "Minamata City, Kumamoto Prefecture";
   case 4320600: return "Tamana City, Kumamoto Prefecture";
   case 4320800: return "Yamaga City, Kumamoto Prefecture";
   case 4321000: return "Kikuchi City, Kumamoto Prefecture";
   case 4321100: return "Uto City, Kumamoto Prefecture";
   case 4321200: return "Kamiamakusa City, Kumamoto Prefecture";
   case 4321300: return "Uki City, Kumamoto Prefecture";
   case 4321400: return "Aso City, Kumamoto Prefecture";
   case 4321500: return "Amakusa City, Kumamoto Prefecture";
   case 4321600: return "Koshi City, Kumamoto Prefecture";
   case 4334800: return "Misato, Kumamoto Prefecture";
   case 4336400: return "Tamahigashi, Kumamoto Prefecture";
   case 4336700: return "Nankan Town, Kumamoto Prefecture";
   case 4336800: return "Nagasu Town, Kumamoto Prefecture";
   case 4336900: return "Nagomi Town, Kumamoto Prefecture";
   case 4340300: return "Otsu Town, Kumamoto Prefecture";
   case 4340400: return "Kikuyo Town, Kumamoto Prefecture";
   case 4342300: return "Minamioguni Town, Kumamoto Prefecture";
   case 4342400: return "Oguni Town, Kumamoto Prefecture";
   case 4342500: return "Ubuyama Village, Kumamoto Prefecture";
   case 4342800: return "Takamori Town, Kumamoto Prefecture";
   case 4343200: return "Nishihara Village, Kumamoto Prefecture";
   case 4343300: return "Minamiaso Village, Kumamoto Prefecture";
   case 4344100: return "Mifune, Kumamoto Prefecture";
   case 4344200: return "Kashima Town, Kumamoto Prefecture";
   case 4344300: return "Mashiki Town, Kumamoto Prefecture";
   case 4344400: return "Kosa Town, Kumamoto Prefecture";
   case 4344700: return "Yamato, Kumamoto Prefecture";
   case 4346800: return "Hikawa Town, Kumamoto Prefecture";
   case 4348200: return "Ashikita, Kumamoto Prefecture";
   case 4348400: return "Tsunagi, Kumamoto Prefecture";
   case 4350100: return "Nishiki, Kumamoto";
   case 4350500: return "Taragi Town, Kumamoto Prefecture";
   case 4350600: return "Yumae, Kumamoto Prefecture";
   case 4350700: return "Minakami Village, Kumamoto Prefecture";
   case 4351000: return "Sagara Village, Kumamoto Prefecture";
   case 4351100: return "Itsuki Village, Kumamoto Prefecture";
   case 4351200: return "Yamae Village, Kumamoto Prefecture";
   case 4351300: return "Kuma Village, Kumamoto Prefecture";
   case 4351400: return "Asagiri Town, Kumamoto Prefecture";
   case 4353100: return "Reihoku, Kumamoto Prefecture";
   case 4399999: return "Other municipalities in Kumamoto Prefecture";
   case 4420100: return "Oita City, Oita Prefecture";
   case 4420200: return "Beppu City, Oita Prefecture";
   case 4420300: return "Nakatsu City, Oita Prefecture";
   case 4420400: return "Hita City, Oita Prefecture";
   case 4420500: return "Saiki City, Oita Prefecture";
   case 4420600: return "Usuki City, Oita Prefecture";
   case 4420700: return "Tsukumi City, Oita Prefecture";
   case 4420800: return "Taketa City, Oita Prefecture";
   case 4420900: return "Bungotakada City, Oita Prefecture";
   case 4421000: return "Kitsuki City, Oita Prefecture";
   case 4421100: return "Usa City, Oita Prefecture";
   case 4421200: return "Bungo Ono City, Oita Prefecture";
   case 4421300: return "Yufu City, Oita Prefecture";
   case 4421400: return "Kunisaki City, Oita Prefecture";
   case 4432200: return "Himeshima Village, Oita Prefecture";
   case 4434100: return "Hiji Town, Oita Prefecture";
   case 4446100: return "Kokonoe Town, Oita Prefecture";
   case 4446200: return "Kusu Town, Oita Prefecture";
   case 4499999: return "other municipalities in Oita Prefecture";
   case 4520100: return "Miyazaki City, Miyazaki Prefecture";
   case 4520200: return "Miyakonojo, Miyazaki Prefecture";
   case 4520300: return "Nobeoka City, Miyazaki Prefecture";
   case 4520400: return "Nichinan City, Miyazaki Prefecture";
   case 4520500: return "Kobayashi City, Miyazaki Prefecture";
   case 4520600: return "Hyuga City, Miyazaki Prefecture";
   case 4520700: return "Kuma City, Miyazaki Prefecture";
   case 4520800: return "Miyazaki Saito City";
   case 4520900: return "Ebino City, Miyazaki Prefecture";
   case 4534100: return "Mitsumata, Miyazaki Prefecture";
   case 4536100: return "Takahara Town, Miyazaki Prefecture";
   case 4538200: return "Kunitomi Town, Miyazaki Prefecture";
   case 4538300: return "Aya Town, Miyazaki Prefecture";
   case 4540100: return "Takanabe Town, Miyazaki Prefecture";
   case 4540200: return "Shintomicho, Miyazaki Prefecture";
   case 4540300: return "Nishimera Village, Miyazaki Prefecture";
   case 4540400: return "Kijo Town, Miyazaki Prefecture";
   case 4540500: return "Kawaminami Town, Miyazaki Prefecture";
   case 4540600: return "Tsuno Town, Miyazaki Prefecture";
   case 4542100: return "Kadogawa Town, Miyazaki Prefecture";
   case 4542900: return "Morotsuka Village, Miyazaki Prefecture";
   case 4543000: return "Shiiba Village, Miyazaki Prefecture";
   case 4543100: return "Misato Town, Miyazaki Prefecture";
   case 4544100: return "Takachiho Town, Miyazaki Prefecture";
   case 4544200: return "Hinokage Town, Miyazaki Prefecture";
   case 4544300: return "Gokase Town, Miyazaki Prefecture";
   case 4599999: return "Other municipalities in Miyazaki Prefecture";
   case 4620100: return "Kagoshima City, Kagoshima Prefecture";
   case 4620300: return "Kanoya City, Kagoshima Prefecture";
   case 4620400: return "Makurazaki City, Kagoshima Prefecture";
   case 4620600: return "Akune City, Kagoshima Prefecture";
   case 4620800: return "Izumi City, Kagoshima Prefecture";
   case 4621000: return "Ibusuki City, Kagoshima Prefecture";
case 4621300: return "Nishinoomote City, Kagoshima Prefecture";
   case 4621400: return "Tarumizu City, Kagoshima Prefecture";
   case 4621500: return "Satsumasendai City, Kagoshima Prefecture";
   case 4621600: return "Hioki City, Kagoshima Prefecture";
   case 4621700: return "Soo City, Kagoshima Prefecture";
   case 4621800: return "Kirishima City, Kagoshima Prefecture";
   case 4621900: return "Ichikikushikino City, Kagoshima Prefecture";
   case 4622000: return "Minamisatsuma City, Kagoshima Prefecture";
   case 4622100: return "Shibushi City, Kagoshima Prefecture";
   case 4622200: return "Amami City, Kagoshima Prefecture";
   case 4622300: return "Minamikyushu City, Kagoshima Prefecture";
   case 4622400: return "Isa City, Kagoshima Prefecture";
   case 4622500: return "Aira City, Kagoshima Prefecture";
   case 4630300: return "Mishima Village, Kagoshima Prefecture";
   case 4630400: return "Toshima Village, Kagoshima Prefecture";
   case 4639200: return "Satsuma Town, Kagoshima Prefecture";
   case 4640400: return "Nagashima Town, Kagoshima Prefecture";
   case 4645200: return "Yusui Town, Kagoshima Prefecture";
   case 4646800: return "Osaki Town, Kagoshima Prefecture";
   case 4648200: return "Higashikushira Town, Kagoshima Prefecture";
   case 4649000: return "Kinkocho, Kagoshima Prefecture";
   case 4649100: return "Minamiosumi Town, Kagoshima Prefecture";
   case 4649200: return "Kimotsuki Town, Kagoshima Prefecture";
   case 4650100: return "Nakatane Town, Kagoshima Prefecture";
   case 4650200: return "Minamitane Town, Kagoshima Prefecture";
   case 4650500: return "Yakushima Town, Kagoshima Prefecture";
   case 4652300: return "Yamato Village, Kagoshima Prefecture";
   case 4652400: return "Uken Village, Kagoshima Prefecture";
   case 4652500: return "Setouchi Town, Kagoshima Prefecture";
   case 4652700: return "Tatsugo Town, Kagoshima Prefecture";
   case 4652900: return "Kikai, Kagoshima Prefecture";
   case 4653000: return "Tokunoshima Town, Kagoshima Prefecture";
   case 4653100: return "Amagi Town, Kagoshima Prefecture";
   case 4653200: return "Isen Town, Kagoshima Prefecture";
   case 4653300: return "Wadomari, Kagoshima Prefecture";
   case 4653400: return "China Town, Kagoshima Prefecture";
   case 4653500: return "Yoron Town, Kagoshima Prefecture";
   case 4699999: return "Other municipalities in Kagoshima Prefecture";
   case 4720100: return "Naha City, Okinawa Prefecture";
   case 4720500: return "Ginowan City, Okinawa Prefecture";
   case 4720700: return "Ishigaki City, Okinawa Prefecture";
   case 4720800: return "Urasoe City, Okinawa Prefecture";
   case 4720900: return "Nago City, Okinawa Prefecture";
   case 4721000: return "Itoman City, Okinawa Prefecture";
   case 4721100: return "Okinawa City, Okinawa Prefecture";
   case 4721200: return "Tomigusuku City, Okinawa Prefecture";
   case 4721300: return "Uruma City, Okinawa Prefecture";
   case 4721400: return "Miyakojima City, Okinawa Prefecture";
   case 4721500: return "Nanjo City, Okinawa Prefecture";
   case 4730100: return "Kunigami Village, Okinawa Prefecture";
   case 4730200: return "Ogimi Village, Okinawa Prefecture";
   case 4730300: return "Higashi Village, Okinawa Prefecture";
   case 4730600: return "Nakijin Village, Okinawa Prefecture";
   case 4730800: return "Motobu Town, Okinawa Prefecture";
   case 4731100: return "Onna Village, Okinawa Prefecture";
   case 4731300: return "Ginoza Village, Okinawa Prefecture";
   case 4731400: return "Kin Town, Okinawa Prefecture";
   case 4731500: return "Ie Village, Okinawa Prefecture";
   case 4732400: return "Yomitan, Okinawa";
   case 4732500: return "Kadena Town, Okinawa Prefecture";
   case 4732600: return "Chatan Town, Okinawa Prefecture";
   case 4732700: return "Kitanakagusuku, Okinawa";
   case 4732800: return "Nakagusuku, Okinawa";
   case 4732900: return "Nishihara Town, Okinawa Prefecture";
   case 4734800: return "Yonabaru Town, Okinawa Prefecture";
   case 4735000: return "Haebaru Town, Okinawa Prefecture";
   case 4735300: return "Tokashiki Village, Okinawa Prefecture";
   case 4735400: return "Zamami Village, Okinawa Prefecture";
   case 4735500: return "Aguni Village, Okinawa Prefecture";
   case 4735600: return "Tonaki Village, Okinawa Prefecture";
   case 4735700: return "Minamidaito Village, Okinawa Prefecture";
   case 4735800: return "Kitadaito Village, Okinawa Prefecture";
   case 4735900: return "Iheya Village, Okinawa Prefecture";
   case 4736000: return "Izena Village, Okinawa Prefecture";
   case 4736100: return "Kumejima Town, Okinawa Prefecture";
   case 4736200: return "Yaese Town, Okinawa Prefecture";
   case 4737500: return "Tarama Village, Okinawa Prefecture";
   case 4738100: return "Taketomi Town, Okinawa Prefecture";
   case 4738200: return "Yonaguni, Okinawa";
   case 4799999: return "Other municipalities in Okinawa Prefecture";
  default:
    const char *pref;
    switch (code / 100000) {
    case 1: pref = "Hokkaido"; break;
     case 2: pref = "Aomori Prefecture"; break;
     case 3: pref = "Iwate Prefecture"; break;
     case 4: pref = "Miyagi Prefecture"; break;
     case 5: pref = "Akita Prefecture"; break;
     case 6: pref = "Yamagata Prefecture"; break;
     case 7: pref = "Fukushima"; break;
     case 8: pref = "Ibaraki Prefecture"; break;
     case 9: pref = "Tochigi Prefecture"; break;
     case 10: pref = "Gunma Prefecture"; break;
     case 11: pref = "Saitama Prefecture"; break;
     case 12: pref = "Chiba Prefecture"; break;
     case 13: pref = "Tokyo"; break;
     case 14: pref = "Kanagawa Prefecture"; break;
     case 15: pref = "Niigata Prefecture"; break;
     case 16: pref = "Toyama Prefecture"; break;
     case 17: pref = "Ishikawa Prefecture"; break;
     case 18: pref = "Fukui Prefecture"; break;
     case 19: pref = "Yamanashi Prefecture"; break;
     case 20: pref = "Nagano Prefecture"; break;
     case 21: pref = "Gifu Prefecture"; break;
     case 22: pref = "Shizuoka Prefecture"; break;
     case 23: pref = "Aichi Prefecture"; break;
     case 24: pref = "Mie Prefecture"; break;
     case 25: pref = "Shiga Prefecture"; break;
     case 26: pref = "Kyoto"; break;
     case 27: pref = "Osaka Prefecture"; break;
     case 28: pref = "Hyogo Prefecture"; break;
     case 29: pref = "Nara Prefecture"; break;
     case 30: pref = "Wakayama Prefecture"; break;
     case 31: pref = "Tottori Prefecture"; break;
     case 32: pref = "Shimane Prefecture"; break;
     case 33: pref = "Okayama Prefecture"; break;
     case 34: pref = "Hiroshima"; break;
     case 35: pref = "Yamaguchi Prefecture"; break;
     case 36: pref = "Tokushima Prefecture"; break;
     case 37: pref = "Kagawa Prefecture"; break;
     case 38: pref = "Ehime Prefecture"; break;
     case 39: pref = "Kochi Prefecture"; break;
     case 40: pref = "Fukuoka Prefecture"; break;
     case 41: pref = "Saga Prefecture"; break;
     case 42: pref = "Nagasaki Prefecture"; break;
     case 43: pref = "Kumamoto Prefecture"; break;
     case 44: pref = "Oita Prefecture"; break;
     case 45: pref = "Miyazaki Prefecture"; break;
     case 46: pref = "Kagoshima Prefecture"; break;
     case 47: pref = "Okinawa Prefecture"; break;
     default: pref = "Other"; break;
     }
     snprintf(_undefMessage, sizeof(_undefMessage),
              "City of %s (code number: %d)", pref, code);
     return _undefMessage;
   }
}
#endif // defined(QZQSM_ENABLE_DC8) || defined(QZQSM_ENABLE_DC9)

#ifdef QZQSM_ENABLE_DC8

int QZQSM::filter_dc8()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc8()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC8_REPORT, it2str(_Header.It), _jstAtMo, _jstAtD, _jstAtH, _jstAtMi,
                   dc8vo2str(_u.Dc8.Vo), dc8td2str(_u.Dc8.TdD, _u.Dc8.TdH, _u.Dc8.TdM, _u.Dc8.Du),
                   dc8dw2str(_u.Dc8.Dw));
  int num;
  for (num = 0; num < 5; num++) {
    if (_u.Dc8.Pl[num] != 0) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC8_REPORT2, dc8pl2str(_u.Dc8.Pl[num]));
    }
  }
}

void QZQSM::decode_dc8()
{
  _u.Dc8.Du    = get_val(50, 3);
  _u.Dc8.TdD   = get_val(53, 5);
  _u.Dc8.TdH   = get_val(58, 5);
  _u.Dc8.TdM   = get_val(63, 6);
  _u.Dc8.Dw    = get_val(69, 7);
  _u.Dc8.Vo    = get_val(76, 12);
  int num;
  for (num = 0; num < 5; num++) {
    _u.Dc8.Pl[num] = get_val(88 + (23 * num), 23);
  }
  if ((_u.Dc8.TdH != 31) && (_u.Dc8.TdM != 63))
    utc2jst(_Header.AtMo, _u.Dc8.TdD, _u.Dc8.TdH, _u.Dc8.TdM);
}
#endif // QZQSM_ENABLE_DC8

#ifdef QZQSM_ENABLE_DC9
//===============================================================
// Disaster Category Code 9
// JMA-DC Report (Ash Fall)

#define DC9_REPORT \
   "Disaster report (ashfall) (%s)\n\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n" \
   "%s\n" \
   "volcano name: %s\n" \
   "Date: %d days %d hours %d minutes\n\n"

#define DC9_REPORT2 \
   "time since base time: %d hours\n" \
   "Phenomenon: %s\n" \
   "%s\n\n"

// Warning State
const char* QZQSM::dc9dw2str(int code)
{
   switch (code) {
   case 1: return "small ash fall";
   case 2: return "Slightly heavy ashfall";
   case 3: return "heavy ash fall";
   case 4: return "small cinder fall";
   case 7: return "Other disaster prevention weather information element 2";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Disaster weather information element 2 (code number: %d)", code);
     return _undefMessage;
   }
}

int QZQSM::filter_dc9()
{
   // You can filter out the specific region or information.
   return 1;
}

void QZQSM::report_dc9()
{
   _len += snprintf(&_message[_len], sizeof(_message) - _len,
                    DC9_REPORT, it2str(_Header.It), _jstAtMo, _jstAtD, _jstAtH, _jstAtMi,
                    (_u.Dc9.Dw1 == 1) ? "Tephra Fall Forecast (Preliminary)" : "Tephra Fall Forecast (Details)",
                    dc8vo2str(_u.Dc9.Vo), _u.Dc9.TdD, _u.Dc9.TdH, _u.Dc9.TdM);
   int num;
   for (num = 0; num < 4; num++) {
     if (_u.Dc9.site[num].Pl != 0) {
       _len += snprintf(&_message[_len], sizeof(_message) - _len,
                        DC9_REPORT2, _u.Dc9.site[num].Ho, dc9dw2str(_u.Dc9.site[num].Dw2),
                        dc8pl2str(_u.Dc9.site[num].Pl));
     }
   }
}

void QZQSM::decode_dc9()
{
  _u.Dc9.TdD   = get_val(53, 5);
  _u.Dc9.TdH   = get_val(58, 5);
  _u.Dc9.TdM   = get_val(63, 6);
  _u.Dc9.Dw1   = get_val(69, 2);
  _u.Dc9.Vo    = get_val(71, 12);
  int num;
  for (num = 0; num < 4; num++) {
    _u.Dc9.site[num].Ho  = get_val(83 + (29 * num), 3);
    _u.Dc9.site[num].Dw2 = get_val(86 + (29 * num), 3);
    _u.Dc9.site[num].Pl  = get_val(89 + (29 * num), 23);
  }
  utc2jst(_Header.AtMo, _u.Dc9.TdD, _u.Dc9.TdH, _u.Dc9.TdM);
}
#endif // QZQSM_ENABLE_DC9

#ifdef QZQSM_ENABLE_DC10
//===============================================================
// Disaster Category Code 10
// JMA-DC Report (Weather)

#define DC10_REPORT \
   "Disaster Report (Weather)(%s)\n\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n"

#define DC10_REPORT2 \
   "%s: %s\n"

// Warning State
const char* QZQSM::dc10ar2str(int code)
{
   switch (code) {
   case 1: return "Announcement";
   case 2: return "release";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Presentation status (code number: %d)", code);
     return _undefMessage;
   }
}

// Disaster Sub-Category (Region)
const char* QZQSM::dc10ww2str(int code)
{
   switch (code) {
   case 1: return "storm warning";
   case 2: return "heavy rain emergency warning";
   case 3: return "Special storm warning";
   case 4: return "heavy snow warning";
   case 5: return "High wave emergency warning";
   case 6: return "storm surge warning";
   case 7: return "All weather emergency warnings";
   case 21: return "Record short heavy rain warning";
   case 22: return "tornado warning information";
   case 23: return "Landslide warning information";
   case 31: return "other information elements such as alarms";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "alarm information element (code number: %d)", code);
     return _undefMessage;
   }
}

// Prefectural Forecast Region
const char* QZQSM::dc10pl2str(int code)
{
   switch (code) {
   case 11000: return "Soya region";
   case 12000: return "Kamikawa/Rumoi region";
   case 12010: return "Kamikawa region";
   case 12020: return "Rumoi region";
   case 13000: return "Abashiri Kitami Monbetsu";
   case 14010: return "Nemuro region";
   case 14020: return "Kushiro region";
   case 14030: return "Tokachi";
   case 14100: return "Kushiro/Nemuro region";
   case 15000: return "Iburi/Hidaka region";
   case 15010: return "Iburi region";
   case 15020: return "Hidaka region";
   case 16000: return "Ishikari/Sorachi/Shiribeshi region";
   case 16010: return "Ishikari region";
   case 16020: return "Sorachi region";
   case 16030: return "Shiribeshi region";
   case 16100: return "Ishikari/Sorachi region";
   case 17000: return "Oshima/Hiyama area";
   case 17010: return "Oshima region";
   case 17020: return "Hiyama region";
   case 20000: return "Aomori Prefecture";
   case 30000: return "Iwate Prefecture";
   case 40000: return "Miyagi Prefecture";
   case 50000: return "Akita Prefecture";
   case 60000: return "Yamagata Prefecture";
   case 70000: return "Fukushima Prefecture";
   case 80000: return "Ibaraki Prefecture";
   case 90000: return "Tochigi Prefecture";
   case 100000: return "Gunma Prefecture";
   case 110000: return "Saitama Prefecture";
   case 120000: return "Chiba Prefecture";
   case 130000: return "Tokyo";
   case 130010: return "Tokyo area";
   case 130020: return "Northern Izu Islands";
   case 130030: return "Southern Izu Islands";
   case 140000: return "Kanagawa Prefecture";
   case 150000: return "Niigata Prefecture";
   case 160000: return "Toyama Prefecture";
   case 170000: return "Ishikawa Prefecture";
   case 180000: return "Fukui Prefecture";
   case 190000: return "Yamanashi Prefecture";
   case 200000: return "Nagano Prefecture";
   case 210000: return "Gifu Prefecture";
   case 220000: return "Shizuoka Prefecture";
   case 230000: return "Aichi Prefecture";
   case 240000: return "Mie Prefecture";
   case 250000: return "Shiga Prefecture";
   case 260000: return "Kyoto";
   case 270000: return "Osaka";
   case 280000: return "Hyogo Prefecture";
   case 290000: return "Nara Prefecture";
   case 300000: return "Wakayama Prefecture";
   case 310000: return "Tottori Prefecture";
   case 320000: return "Shimane Prefecture";
   case 330000: return "Okayama Prefecture";
   case 340000: return "Hiroshima";
   case 350000: return "Yamaguchi Prefecture";
   case 360000: return "Tokushima Prefecture";
   case 370000: return "Kagawa Prefecture";
   case 380000: return "Ehime Prefecture";
   case 390000: return "Kochi Prefecture";
   case 400000: return "Fukuoka Prefecture";
   case 410000: return "Saga Prefecture";
   case 420000: return "Nagasaki Prefecture";
   case 430000: return "Kumamoto Prefecture";
   case 440000: return "Oita Prefecture";
   case 450000: return "Miyazaki Prefecture";
   case 460000: return "Kagoshima Prefecture";
   case 460040: return "Amami region";
   case 460100: return "Kagoshima (excluding Amami)";
   case 471000: return "Okinawa main island region";
   case 472000: return "Daito Island Region";
   case 473000: return "Miyakojima region";
   case 474000: return "Yaeyama region";
   case 500000: return "Other Prefectural Forecast Areas";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "prefectural forecast area (code number: %d)", code);
     return _undefMessage;
   }
}

int QZQSM::filter_dc10()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc10()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC10_REPORT, dc10ar2str(_u.Dc10.Ar),
                   _jstAtMo, _jstAtD, _jstAtH, _jstAtMi);
  int num;
  for (num = 0; num < 6; num++) {
    if (_u.Dc10.site[num].Ww == 0) break;
    _len += snprintf(&_message[_len], sizeof(_message) - _len,
                     DC10_REPORT2, dc10ww2str(_u.Dc10.site[num].Ww), dc10pl2str(_u.Dc10.site[num].Pl));
  }
}

void QZQSM::decode_dc10()
{
  _u.Dc10.Ar = get_val(53, 3);
  int num;
  for (num = 0; num < 6; num++) {
    _u.Dc10.site[num].Ww = get_val(56 + (24 * num), 5);
    _u.Dc10.site[num].Pl = get_val(61 + (24 * num), 19);
  }
}
#endif // QZQSM_ENABLE_DC10

#ifdef QZQSM_ENABLE_DC11
//===============================================================
// Disaster Category Code 11
// JMA-DC Report (Flood)

#define DC11_REPORT \
   "Disaster Report (Flood)(%s)\n\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n"

#define DC11_REPORT2 \
   "%s: %s\n"

// Warning Level
const char* QZQSM::dc11lv2str(int code)
{
   switch (code) {
   case 1: return "alarm reset";
   case 2: return "flood warning information";
   case 3: return "flood danger information";
   case 4: return "flooding information";
   case 15: return "Other alert levels";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Warning level (code number: %d)", code);
     return _undefMessage;
   }
}

const char* QZQSM::dc11pl2str(uint64_t code)
{
  switch (code) {
case 10175000100: return "Shinkawa (Central Hokkaido)";
   case 19999999999: return "Other rivers in Hokkaido";
   case 20036000100: return "Tsuji River/Komagome River (Aomori Prefecture)";
   case 29999999999: return "Other rivers in Aomori Prefecture";
   case 39999999999: return "Other rivers in Iwate Prefecture";
   case 40028000100: return "Nanakita River (Miyagi Prefecture)";
   case 49999999999: return "Other rivers in Miyagi Prefecture";
   case 59999999999: return "Other rivers in Akita Prefecture";
   case 60016000100: return "Hyuga River (Yamagata Prefecture)";
   case 69999999999: return "Other rivers in Yamagata Prefecture";
   case 70006000100: return "Utagawa (Fukushima)";
   case 70010000100: return "Nitta River (Fukushima Prefecture)";
   case 70028000100: return "Natsuigawa (Fukushima Prefecture)";
   case 79999999999: return "Other rivers in Fukushima Prefecture";
   case 89999999999: return "Other rivers in Ibaraki Prefecture";
   case 99999999999: return "Other rivers in Tochigi Prefecture";
   case 109999999999: return "Other rivers in Gunma Prefecture";
   case 119999999999: return "Other rivers in Saitama Prefecture";
   case 129999999999: return "Other rivers in Chiba Prefecture";
   case 130005000100: return "Meguro River (Tokyo)";
   case 130006000100: return "Shibuyagawa/Furukawa (Tokyo)";
   case 139999999999: return "Other rivers in Tokyo";
   case 140019000100: return "Sakawa River (Kanagawa Prefecture)";
   case 149999999999: return "Other rivers in Kanagawa Prefecture";
   case 159999999999: return "Other rivers in Niigata Prefecture";
   case 169999999999: return "Other rivers in Toyama Prefecture";
   case 179999999999: return "Other rivers in Ishikawa Prefecture";
   case 180006000100: return "Minamikawa (Fukui Prefecture)";
   case 180014000100: return "Sho River (Fukui Prefecture)";
   case 189999999999: return "Other rivers in Fukui Prefecture";
   case 199999999999: return "Other rivers in Yamanashi Prefecture";
   case 209999999999: return "Other rivers in Nagano Prefecture";
   case 219999999999: return "Other rivers in Gifu Prefecture";
   case 220062000100: return "Seto River / Asahina River (Shizuoka Prefecture)";
   case 220079000100: return "Ota River/Haranotani River (Shizuoka Prefecture)";
   case 220081000100: return "Miyakodagawa (Shizuoka Prefecture)";
   case 229999999999: return "Other rivers in Shizuoka Prefecture";
   case 230029000100: return "Sakaigawa/Aizumagawa (Aichi Prefecture)";
   case 230052000100: return "Amashira River (Aichi Prefecture)";
   case 230054000100: return "Nikko River (Aichi Prefecture)";
   case 239999999999: return "Other rivers in Aichi Prefecture";
   case 249999999999: return "Other rivers in Mie Prefecture";
   case 259999999999: return "Other rivers in Shiga Prefecture";
   case 269999999999: return "Other rivers in Kyoto Prefecture";
   case 270013000100: return "Otsugawa/Makiogawa (Osaka)";
   case 270013000200: return "Ushitakigawa (Osaka)";
   case 279999999999: return "Other rivers in Osaka Prefecture";
   case 280014000100: return "Mukogawa (Hyogo Prefecture)";
   case 280053000100: return "Ichikawa (Hyogo Prefecture)";
   case 280064000100: return "Chikusagawa (Hyogo Prefecture)";
   case 289999999999: return "Other rivers in Hyogo Prefecture";
   case 299999999999: return "Other rivers in Nara Prefecture";
   case 300013000100: return "Kozagawa (Wakayama Prefecture)";
   case 300066000100: return "Hidakagawa (Wakayama Prefecture)";
   case 300077000100: return "Arita River (Wakayama Prefecture)";
   case 309999999999: return "Other rivers in Wakayama Prefecture";
   case 310027000100: return "Yura River (Tottori Prefecture)";
   case 319999999999: return "Other rivers in Tottori Prefecture";
   case 320004000100: return "Masuda River (Shimane Prefecture)";
   case 320011000100: return "Sufukawa (Shimane Prefecture)";
   case 329999999999: return "Other rivers in Shimane Prefecture";
   case 330009000100: return "Sasagase River/Ashimori River (Okayama Prefecture)";
   case 339999999999: return "Other rivers in Okayama Prefecture";
   case 340013000100: return "Numata River (Hiroshima Prefecture)";
   case 340021000100: return "Kurosegawa (Hiroshima Prefecture)";
   case 349999999999: return "Other rivers in Hiroshima Prefecture";
   case 350002000102: return "Lower Nishiki River (Yamaguchi Prefecture)";
   case 350002000103: return "Nishiki River Midstream (Yamaguchi Prefecture)";
   case 350019000100: return "Shimadagawa (Yamaguchi Prefecture)";
   case 350036000100: return "Sawaranogawa (Yamaguchi Prefecture)";
   case 350036001900: return "Nibogawa (Yamaguchi Prefecture)";
   case 350046000100: return "Koto River (Yamaguchi Prefecture)";
   case 359999999999: return "Other rivers in Yamaguchi Prefecture";
   case 360007000100: return "Katsuura River (Tokushima Prefecture)";
   case 369999999999: return "Other rivers in Tokushima Prefecture";
   case 370026000100: return "Kotogawa (Kagawa Prefecture)";
   case 379999999999: return "Other rivers in Kagawa Prefecture";
   case 389999999999: return "Other rivers in Ehime Prefecture";
   case 399999999999: return "Other rivers in Kochi Prefecture";
   case 400018000100: return "Mikasagawa (Fukuoka)";
   case 409999999999: return "Other rivers in Fukuoka Prefecture";
   case 419999999999: return "Other rivers in Saga Prefecture";
   case 429999999999: return "Other rivers in Nagasaki Prefecture";
   case 439999999999: return "Other rivers in Kumamoto Prefecture";
   case 440008000100: return "Ekidategawa (Oita Prefecture)";
   case 449999999999: return "Other rivers in Oita Prefecture";
   case 450026000100: return "Kiyotake River (Miyazaki Prefecture)";
   case 450040000100: return "Hirowatagawa (Miyazaki Prefecture)";
   case 450040000700: return "Sakatanigawa (Miyazaki Prefecture)";
   case 459999999999: return "Other rivers in Miyazaki Prefecture";
   case 460060000100: return "Manose River/Kaseda River (Kagoshima Prefecture)";
   case 469999999999: return "Other rivers in Kagoshima Prefecture";
   case 479999999999: return "Other rivers in Okinawa Prefecture";
   case 809999999999: return "Other rivers in Okinawa Prefecture";
   case 810101000100: return "Teshiogawa (North Hokkaido)";
   case 810101008500: return "Nayoro River (North Hokkaido)";
   case 810102000100: return "Rumoi River (North Hokkaido)";
   case 810103000101: return "Upstream Ishikari River (North Hokkaido)";
   case 810103000102: return "Lower Ishikari River (Central Hokkaido)";
   case 810103003100: return "Toyohira River (Central Hokkaido)";
   case 810103008100: return "Chitose River (Central Hokkaido)";
   case 810103011900: return "Yubari River (Central Hokkaido)";
   case 810103018200: return "Ikushunbetsu River (Central Hokkaido)";
   case 810103025001: return "Upstream Sorachi River (North Hokkaido)";
   case 810103025002: return "Lower Sorachi River (Central Hokkaido)";
   case 810103033400: return "Uryu River (Central Hokkaido)";
   case 810103040900: return "Chubetsu River (North Hokkaido)";
case 810103041000: return "Biei River (Hokkaido Dohoku)";
   case 810103044200: return "Gyushubetsu River (Hokkaido Dohoku)";
   case 810104000100: return "Shiribetsu River (Central Hokkaido)";
   case 810105000100: return "Shiribeshi Toshibetsu River (Southern Hokkaido)";
   case 810106000100: return "Mukawa (Southern Hokkaido)";
   case 810107000100: return "Saru River (Southern Hokkaido)";
   case 810108000100: return "Tokachi River (East Hokkaido)";
   case 810108003400: return "Toshibetsu River (East Hokkaido)";
   case 810108011400: return "Satsunai River (East Hokkaido)";
   case 810108013900: return "Otofuke River (East Hokkaido)";
   case 810109000100: return "Kushiro River/Shin Kushiro River (East Hokkaido)";
   case 810110000100: return "Abashiri River (East Hokkaido)";
   case 810110001000: return "Bihoro River (East Hokkaido)";
   case 810111000100: return "Tokoro River (East Hokkaido)";
   case 810111002400: return "Mugagawa (Eastern Hokkaido)";
   case 810112000100: return "Yubetsu River (East Hokkaido)";
   case 810113000100: return "Nagisa Namegawa (East Hokkaido)";
   case 819999999999: return "Other rivers in Hokkaido";
   case 820201000101: return "Upstream Abukuma River (Fukushima/Miyagi)";
   case 820201000102: return "Lower Abukuma River (Miyagi Prefecture)";
   case 820201000400: return "Shiroishigawa (Miyagi Prefecture)";
   case 820201009900: return "Arakawa (Fukushima)";
   case 820202000100: return "Natori River (Miyagi Prefecture)";
   case 820202001100: return "Hirose River (Miyagi Prefecture)";
   case 820203000100: return "Naruse River (Miyagi Prefecture)";
   case 820203000400: return "Yoshida River (Miyagi Prefecture)";
   case 820204000101: return "Upstream Kitakami River (Iwate Prefecture)";
   case 820204000102: return "Lower Kitakami River (Miyagi Prefecture)";
   case 820204001800: return "Old Kitakami River (Miyagi Prefecture)";
   case 820204001900: return "Hasagawa (Miyagi)";
   case 820204007100: return "Eaigawa (Miyagi Prefecture)";
   case 820204035600: return "Sarugaishikawa (Iwate Prefecture)";
   case 820204048200: return "Shizukuishikawa (Iwate Prefecture)";
   case 820205000102: return "Lower Mabechi River (Aomori Prefecture)";
   case 820205000103: return "middle stream of the Mabechi River (Aomori Prefecture)";
   case 820206000100: return "Takase River (Lake Ogawara) (Aomori Prefecture)";
   case 820207000100: return "Iwaki River (Aomori Prefecture)";
   case 820207003500: return "Togawa (Aomori Prefecture)";
   case 820207006101: return "Upstream Hirakawa (Aomori Prefecture)";
   case 820207006102: return "Downstream Hirakawa (Aomori Prefecture)";
   case 820208000100: return "Yoneshiro River (Akita Prefecture)";
   case 820209000101: return "Upstream Omonogawa (Akita Prefecture)";
   case 820209000102: return "Lower Omono River (Akita Prefecture)";
   case 820209000400: return "Taihei River (Akita Prefecture)";
   case 820209005500: return "Tamagawa (Akita)";
   case 820209018700: return "Minasegawa (Akita Prefecture)";
   case 820210000100: return "Koyoshikawa (Akita Prefecture)";
   case 820211000101: return "Upstream Mogami River (Yamagata)";
   case 820211000102: return "Lower Mogami River (Yamagata Prefecture)";
   case 820211000103: return "Midway Mogami River (Yamagata Prefecture)";
   case 820211007300: return "Sakegawa (Yamagata Prefecture)";
   case 820211017000: return "Mogami Ogunigawa (Yamagata Prefecture)";
   case 820211022100: return "Niugawa (Yamagata Prefecture)";
   case 820211030701: return "Upstream Sugawa (Yamagata Prefecture)";
   case 820211030702: return "Lower Sugawa (Yamagata Prefecture)";
   case 820211048700: return "Yashiro River (Yamagata Prefecture)";
   case 820212000100: return "Akagawa (Yamagata Prefecture)";
   case 820212000200: return "Oyama River (Yamagata Prefecture)";
   case 829999999999: return "Other rivers in the Tohoku region";
   case 830301000100: return "Kujigawa (Ibaraki Prefecture)";
   case 830302000100: return "Nakagawa (Tochigi/Ibaraki)";
   case 830302000101: return "Upstream Naka River (Tochigi Prefecture)";
   case 830302008300: return "Sakagawa (Tochigi Prefecture)";
   case 830302009400: return "Arakawa (Tochigi Prefecture)";
   case 830302014300: return "Hokigawa (Tochigi Prefecture)";
   case 830302014700: return "Jao River (Tochigi Prefecture)";
   case 830302018300: return "Yosasagawa (Tochigi Prefecture)";
   case 830303000101: return "Upstream Tone River (Gunma, Ibaraki, Chiba, Saitama)";
   case 830303000102: return "Lower Tone River (Ibaraki Prefecture/Chiba Prefecture)";
   case 830303000103: return "Middle Tone River (Ibaraki Prefecture/Chiba Prefecture)";
   case 830303002800: return "Kasumigaura/Kitaura (Ibaraki/Chiba)";
   case 830303004600: return "Sakuragawa (Ibaraki Prefecture)";
case 830303015200: return "Kokaigawa (Tochigi/Ibaraki)";
   case 830303015201: return "Upstream Kogai River (Tochigi Prefecture)";
   case 830303017900: return "Wuying River (Tochigi Prefecture)";
   case 830303020300: return "Kinugawa (Tochigi/Ibaraki)";
   case 830303021100: return "Tagawa (Tochigi Prefecture)";
   case 830303030400: return "Edogawa (Ibaraki/Saitama/Tokyo/Chiba)";
   case 830303033900: return "Nakagawa (Saitama/Tokyo)";
   case 830303043600: return "Ayase River (Yakou section) (Saitama/Tokyo)";
   case 830303043603: return "Ayase River Midstream (Ichinohashi Section) (Saitama Prefecture)";
   case 830303046101: return "Upstream Watarase River (Gunma and Tochigi prefectures)";
   case 830303046102: return "Lower Watarase River (Tochigi, Ibaraki, Gunma)";
   case 830303048000: return "Omoigawa (Tochigi Prefecture)";
   case 830303048100: return "Sugatagawa (Tochigi Prefecture)";
   case 830303049400: return "Kurokawa (Tochigi Prefecture)";
   case 830303051700: return "Naganogawa (Tochigi Prefecture)";
   case 830303053000: return "Akiyama River (Tochigi Prefecture)";
   case 830303054800: return "Fukurogawa (Tochigi Prefecture)";
   case 830303060000: return "Ishida River (Gunma/Saitama)";
   case 830303068900: return "Karasu River Basin (Gunma Prefecture/Saitama Prefecture)";
   case 830303069600: return "Kannagawa (Gunma/Saitama)";
   case 830304000100: return "Arakawa (Saitama/Tokyo)";
   case 830304000300: return "Shibakawa/Shinshibakawa (Saitama/Tokyo)";
   case 830304001200: return "Shingashi River (Saitama Prefecture)";
   case 830304004400: return "Kandagawa (Tokyo)";
   case 830304004700: return "Myoshoji River (Tokyo)";
   case 830304006400: return "Iruma River Basin (Saitama Prefecture)";
   case 830305000100: return "Tama River (Tokyo/Kanagawa)";
   case 830305000500: return "Nogawa/Sengawa (Tokyo)";
   case 830305002000: return "Asakawa (Tokyo)";
   case 830306000100: return "Tsurumi River (Kanagawa Prefecture)";
   case 830307000102: return "Lower Sagami River (Kanagawa Prefecture)";
   case 830307000103: return "Midstream Sagami River (Kanagawa Prefecture)";
   case 830308000100: return "Fuji River (including Kamanashi River) (Yamanashi Prefecture and Shizuoka Prefecture)";
   case 830308039500: return "Fuefukigawa (Yamanashi Prefecture)";
   case 830308045500: return "Arakawa (Yamanashi Prefecture)";
   case 830308065700: return "Shiokawa (Yamanashi Prefecture)";
   case 839999999999: return "Other rivers in the Kanto region";
   case 840401000100: return "Arakawa (Niigata Prefecture)";
   case 840402000100: return "Agano River (Niigata Prefecture)";
   case 840402000101: return "Agagawa (Fukushima)";
   case 840403000100: return "Chikuma River (Nagano Prefecture)";
   case 840403000101: return "Upstream Chikuma River (Nagano Prefecture)";
   case 840403000102: return "Lower Shinano River / Nakanokuchi River (Niigata Prefecture)";
   case 840403000103: return "Shinano River Midstream (Niigata Prefecture)";
   case 840403023700: return "Uonogawa (Niigata Prefecture)";
   case 840403070500: return "Saigawa (Nagano)";
   case 840403070600: return "Susobana River (Nagano Prefecture)";
   case 840403089800: return "Naraigawa (Nagano Prefecture)";
   case 840404000100: return "Sekikawa (Niigata Prefecture)";
   case 840405000100: return "Himekawa (Niigata Prefecture)";
   case 840406000100: return "Kurobe River (Toyama Prefecture)";
   case 840407000100: return "Joganji River (Toyama Prefecture)";
   case 840408000101: return "Miyagawa (Gifu Prefecture)";
   case 840408000102: return "Jinzu River (Toyama Prefecture)";
   case 840409000100: return "Shogawa (Toyama Prefecture)";
   case 840410000100: return "Oyabe River (Toyama Prefecture)";
   case 840411000100: return "Tedorigawa (Ishikawa Prefecture)";
   case 840412000100: return "Kakegawa (Ishikawa Prefecture)";
   case 849999999999: return "Other rivers in the Hokuriku region";
   case 850501000100: return "Kanogawa (Shizuoka Prefecture)";
   case 850502000100: return "Abegawa (Shizuoka Prefecture)";
   case 850503000100: return "Oigawa (Shizuoka Prefecture)";
   case 850504000100: return "Kikugawa (Shizuoka Prefecture)";
   case 850505000101: return "Upstream Tenryu River (Nagano Prefecture)";
   case 850505000102: return "Lower Tenryu River (Shizuoka Prefecture)";
   case 850505071753: return "Lake Suwa (Nagano Prefecture)";
   case 850506000100: return "Toyokawa and Toyokawa Discharge Channel (Aichi Prefecture)";
   case 850507000100: return "Yahagi River (Aichi Prefecture)";
   case 850508000100: return "Shonai River (Gifu Prefecture/Aichi Prefecture)";
   case 850508000200: return "Shinkawa (Aichi Prefecture)";
   case 850509000102: return "Lower Kiso River (Aichi Prefecture, Gifu Prefecture, Mie Prefecture)";
   case 850509000103: return "Midstream of the Kiso River (Gifu Prefecture/Aichi Prefecture)";
   case 850509000202: return "Downstream of the Ibi River (Gifu Prefecture/Mie Prefecture)";
   case 850509000203: return "Midstream of the Ibi River (Gifu Prefecture)";
   case 850509000401: return "Upstream Nagaragawa (Gifu Prefecture)";
   case 850509000402: return "Lower Nagara River (Gifu Prefecture, Aichi Prefecture, Mie Prefecture)";
   case 850509000403: return "Middle Nagara River (Gifu Prefecture)";
   case 850509025500: return "Hida River (Gifu Prefecture)";
   case 850510000100: return "Suzuka River and Suzuka River (Mie Prefecture)";
   case 850511000100: return "Kumode River and Kumode Furukawa (Mie Prefecture)";
   case 850512000100: return "Kushida River (Mie Prefecture)";
   case 850513000100: return "Miyagawa (Mie Prefecture)";
   case 859999999999: return "Other rivers in Chubu";
   case 860601000102: return "Lower Kumano River (Mie Prefecture/Wakayama Prefecture)";
   case 860601000103: return "Middle Kumano River (Hongu Section) (Wakayama Prefecture)";
   case 860601000105: return "Middle Kumano River (daily section) (Wakayama Prefecture)";
   case 860602000100: return "Kinokawa (Nara/Wakayama)";
   case 860603000101: return "Upstream Yamato River (Nara/Osaka)";
   case 860603000102: return "Lower Yamato River (Nara/Osaka)";
   case 860603001300: return "Ishikawa (Osaka)";
   case 860604000101: return "Setagawa (Shiga Prefecture)";
   case 860604000102: return "Yodogawa (Kyoto/Osaka)";
   case 860604000103: return "Ujigawa (Kyoto/Osaka)";
   case 860604000600: return "Neyagawa basin (Osaka)";
   case 860604004700: return "Kanzakigawa/Auigawa (Osaka)";
   case 860604007300: return "Inagawa (Osaka/Hyogo)";
   case 860604016702: return "Downstream of the Katsura River (Kyoto/Osaka)";
   case 860604016703: return "Midstream Katsura River/Sonobe River (Kyoto Prefecture)";
   case 860604018200: return "Kamogawa/Takanogawa (Kyoto)";
   case 860604037101: return "Upstream Kizugawa (Mie Prefecture/Kyoto Prefecture)";
   case 860604037102: return "Lower Kizugawa (Kyoto)";
   case 860604051600: return "Nabari River (Mie Prefecture/Nara Prefecture)";
   case 860604086300: return "Lake Biwa (Shiga Prefecture)";
   case 860604101200: return "Anegawa (Shiga Prefecture)";
   case 860604101300: return "Takatokigawa (Shiga Prefecture)";
   case 860604120300: return "Hinogawa (Shiga Prefecture)";
   case 860604127501: return "Upstream Yasugawa (Shiga Prefecture)";
   case 860604127502: return "Lower Yasu River (Shiga Prefecture)";
   case 860604131100: return "Somakawa(Shiga)";
   case 860605000101: return "Upstream Kakogawa (Hyogo Prefecture)";
   case 860605000102: return "Lower Kakogawa (Hyogo Prefecture)";
   case 860606000101: return "Upstream Ibo River (Hyogo Prefecture)";
   case 860606000102: return "Downstream of the Ibo River (Hyogo Prefecture)";
case 860607000100: return "Kuzuryu River (Fukui Prefecture)";
   case 860607000200: return "Takeda River (Fukui Prefecture)";
   case 860607001902: return "Lower Hino River (Fukui Prefecture)";
   case 860607001903: return "Hinogawa Midstream (Fukui Prefecture)";
   case 860607002200: return "Ashiwa River (Fukui Prefecture)";
   case 860608000100: return "Kitagawa (Fukui)";
   case 860609000102: return "Lower Yura River (Kyoto Prefecture)";
   case 860609000103: return "Middle Yura River (Kyoto Prefecture)";
   case 860610000100: return "Maruyama River (Hyogo Prefecture)";
   case 860610002600: return "Izushigawa (Hyogo Prefecture)";
   case 869999999999: return "Other rivers in the Kinki region";
   case 870701000100: return "Chiyogawa (Tottori Prefecture)";
   case 870701000900: return "Fukurogawa/Shin-Fukurogawa (Tottori Prefecture)";
   case 870702000100: return "Tenjingawa (Tottori Prefecture)";
   case 870702000300: return "Kogamogawa (Tottori Prefecture)";
   case 870702000400: return "Kokufugawa (Tottori Prefecture)";
   case 870703000100: return "Hinogawa (Tottori Prefecture)";
   case 870703000300: return "Hosshoji River (Tottori Prefecture)";
   case 870704000100: return "Hii River (Shimane Prefecture)";
   case 870704002800: return "Iinashi River (Shimane Prefecture)";
   case 870704024400: return "Kobegawa (Shimane)";
   case 870705000101: return "Upstream Enokawa (Hiroshima/Shimane)";
   case 870705000102: return "Downstream of Enokawa (Hiroshima/Shimane)";
   case 870705015700: return "Kanosegawa (Hiroshima)";
   case 870705016300: return "Maarai River (Hiroshima Prefecture)";
   case 870705016400: return "Nishijogawa (Hiroshima)";
   case 870706000100: return "Takatsugawa (Shimane Prefecture)";
   case 870706001700: return "Hikimi River (Shimane Prefecture)";
   case 870707000100: return "Sabagawa (Yamaguchi Prefecture)";
   case 870708000100: return "Kosegawa (Hiroshima/Yamaguchi)";
   case 870709000101: return "Upstream Otagawa (Hiroshima Prefecture)";
   case 870709000102: return "Lower Ota River (Hiroshima Prefecture)";
   case 870709002900: return "Misasagawa (Hiroshima)";
   case 870709004700: return "Neyagawa (Hiroshima)";
   case 870710000100: return "Ashida River (Hiroshima Prefecture)";
   case 870710001100: return "Takayagawa (Hiroshima)";
   case 870711000100: return "Takahashi River (Okayama Prefecture)";
   case 870711000500: return "Odagawa (Okayama Prefecture)";
   case 870712000100: return "Asahikawa (Okayama Prefecture)";
   case 870712000103: return "Asahikawa water system middle Asahikawa (Okayama Prefecture)";
   case 870712000400: return "Hyakken River (Okayama Prefecture)";
   case 870713000100: return "Yoshiigawa (Okayama Prefecture)";
   case 870713002800: return "Kongo River (Okayama Prefecture)";
   case 879999999999: return "Other rivers in Chugoku region";
   case 880801000100: return "Shigenobu River (Ehime Prefecture)";
   case 880802000100: return "Hijikawa (Ehime Prefecture)";
   case 880803000100: return "Shimanto River (Kochi Prefecture)";
   case 880804000100: return "Niyodogawa (Kochi Prefecture)";
   case 880805000100: return "Mononobe River (Kochi Prefecture)";
   case 880806000100: return "Nagagawa (Tokushima Prefecture)";
   case 880807000100: return "Yoshinogawa (Tokushima Prefecture)";
   case 880808000100: return "Tokigawa (Kagawa Prefecture)";
   case 889999999999: return "Other rivers in Shikoku";
   case 890901000101: return "Upstream Ongagawa (Fukuoka)";
   case 890901000102: return "Lower Onga River (Fukuoka Prefecture)";
   case 890901010300: return "Hikosan River (Fukuoka Prefecture)";
   case 890902000100: return "Matsuura River (Saga Prefecture)";
   case 890902001300: return "Tokusuegawa (Saga Prefecture)";
   case 890902004900: return "Kuragi River (Saga Prefecture)";
   case 890903000100: return "Honaki River (Nagasaki Prefecture)";
   case 890904000100: return "Rokkakugawa (Saga)";
   case 890904000300: return "Ushizugawa (Saga Prefecture)";
   case 890905000100: return "Kasegawa (Saga Prefecture)";
   case 890906000102: return "Lower Chikugo River (Fukuoka Prefecture, Saga Prefecture)";
   case 890906000104: return "Chukugo Upper Midstream (Oita Prefecture/Fukuoka Prefecture)";
   case 890907000100: return "Yabegawa (Fukuoka)";
   case 890908000100: return "Kikuchi River system (Kumamoto Prefecture)";
   case 890909000100: return "Shirakawa (Kumamoto Prefecture)";
   case 890910000100: return "Midori River system (Kumamoto Prefecture)";
   case 890911000100: return "Kumagawa (Kumamoto Prefecture)";
   case 890912000101: return "Upstream Kawauchi River (Miyazaki/Kagoshima)";
   case 890912000102: return "Lower Kawauchi River (Kagoshima Prefecture)";
   case 890913000100: return "Komotsuki River System (Kagoshima Prefecture)";
   case 890914000101: return "Upstream Oyodo River (Miyazaki Prefecture)";
   case 890914000102: return "Lower Oyodo River (Miyazaki Prefecture)";
   case 890914003300: return "Honjo River (Miyazaki Prefecture)";
   case 890915000100: return "Komarugawa (Miyazaki Prefecture)";
   case 890916000100: return "Gokase River/Ose River (Miyazaki Prefecture)";
   case 890917000100: return "Banshogawa (Oita Prefecture)";
   case 890918000100: return "Ono river system (Oita Prefecture)";
   case 890919000100: return "Oita River (Oita Prefecture)";
   case 890919001100: return "Nanase River (Oita Prefecture)";
   case 890920000101: return "Upstream Yamakuni River (Oita Prefecture/Fukuoka Prefecture)";
   case 890920000102: return "Lower Yamakuni River (Oita Prefecture/Fukuoka Prefecture)";
   case 899999999999: return "Other rivers in Kyushu";
default:
     const char *pref;
     switch (code / 10000000000) {
     case 1: pref = "Hokkaido"; break;
     case 2: pref = "Aomori Prefecture"; break;
     case 3: pref = "Iwate Prefecture"; break;
     case 4: pref = "Miyagi Prefecture"; break;
     case 5: pref = "Akita Prefecture"; break;
     case 6: pref = "Yamagata Prefecture"; break;
     case 7: pref = "Fukushima"; break;
     case 8: pref = "Ibaraki Prefecture"; break;
     case 9: pref = "Tochigi Prefecture"; break;
     case 10: pref = "Gunma Prefecture"; break;
     case 11: pref = "Saitama Prefecture"; break;
     case 12: pref = "Chiba Prefecture"; break;
     case 13: pref = "Tokyo"; break;
     case 14: pref = "Kanagawa Prefecture"; break;
     case 15: pref = "Niigata Prefecture"; break;
     case 16: pref = "Toyama Prefecture"; break;
     case 17: pref = "Ishikawa Prefecture"; break;
     case 18: pref = "Fukui Prefecture"; break;
     case 19: pref = "Yamanashi Prefecture"; break;
     case 20: pref = "Nagano Prefecture"; break;
     case 21: pref = "Gifu Prefecture"; break;
     case 22: pref = "Shizuoka Prefecture"; break;
     case 23: pref = "Aichi Prefecture"; break;
     case 24: pref = "Mie Prefecture"; break;
     case 25: pref = "Shiga Prefecture"; break;
     case 26: pref = "Kyoto"; break;
     case 27: pref = "Osaka Prefecture"; break;
     case 28: pref = "Hyogo Prefecture"; break;
     case 29: pref = "Nara Prefecture"; break;
     case 30: pref = "Wakayama Prefecture"; break;
     case 31: pref = "Tottori Prefecture"; break;
     case 32: pref = "Shimane Prefecture"; break;
     case 33: pref = "Okayama Prefecture"; break;
     case 34: pref = "Hiroshima"; break;
     case 35: pref = "Yamaguchi Prefecture"; break;
     case 36: pref = "Tokushima Prefecture"; break;
     case 37: pref = "Kagawa Prefecture"; break;
     case 38: pref = "Ehime Prefecture"; break;
     case 39: pref = "Kochi Prefecture"; break;
     case 40: pref = "Fukuoka Prefecture"; break;
     case 41: pref = "Saga Prefecture"; break;
     case 42: pref = "Nagasaki Prefecture"; break;
     case 43: pref = "Kumamoto Prefecture"; break;
     case 44: pref = "Oita Prefecture"; break;
     case 45: pref = "Miyazaki Prefecture"; break;
     case 46: pref = "Kagoshima Prefecture"; break;
     case 47: pref = "Okinawa Prefecture"; break;
     case 80: pref = "Okinawa Prefecture"; break;
     case 81: pref = "Hokkaido"; break;
     case 82: pref = "Tohoku"; break;
     case 83: pref = "Kanto region"; break;
     case 84: pref = "Hokuriku"; break;
     case 85: pref = "Chubu"; break;
     case 86: pref = "Kinki region"; break;
     case 87: pref = "Chugoku region"; break;
     case 88: pref = "Shikoku"; break;
     case 89: pref = "Kyushu"; break;
     default: pref = "Other"; break;
     }
     snprintf(_undefMessage, sizeof(_undefMessage),
              "%s river (code number: %lld)", pref, code);
     return _undefMessage;
   }
}

int QZQSM::filter_dc11()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc11()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC11_REPORT, it2str(_Header.It), _jstAtMo, _jstAtD, _jstAtH, _jstAtMi);
  int num;
  for (num = 0; num < 3; num++) {
    if (_u.Dc11.site[num].Lv == 0) break;
    _len += snprintf(&_message[_len], sizeof(_message) - _len,
                     DC11_REPORT2, dc11lv2str(_u.Dc11.site[num].Lv), dc11pl2str(_u.Dc11.site[num].Pl));
  }
}

void QZQSM::decode_dc11()
{
  uint64_t tmp;
  int num;
  for (num = 0; num < 3; num++) {
    _u.Dc11.site[num].Lv = get_val(53 + (44 * num), 4);
    tmp = (uint64_t)get_val(57 + (44 * num), 20);
    _u.Dc11.site[num].Pl = (tmp << 20) | get_val(77 + (44 * num), 20);
  }
}
#endif // QZQSM_ENABLE_DC11

#ifdef QZQSM_ENABLE_DC12
//===============================================================
// Disaster Category Code 12
// JMA-DC Report (Typhoon)

#define DC12_REPORT \
   "Disaster Report (Typhoon)(%s)\n\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n"

#define DC12_REPORT2 \
   "Typhoon: %d\n" \
   "Base time: %d days %d hours %d minutes (%s) %d hours later\n" \
   "Size: %s\n" \
   "Strength: %s\n" \
   "Latitude/Longitude: %s%d degrees %d minutes %d seconds %s%d degrees %d minutes %d seconds\n" \
   "Central pressure (hPa): %d\n" \
   "Max Wind Speed (m/s): %s\n" \
   "Maximum instantaneous wind speed (m/s): %s\n"

// Type of Reference Time
const char* QZQSM::dc12dt2str(int code)
{
   switch (code) {
   case 1: return "playback";
   case 2: return "estimate";
   case 3: return "forecast";
   default: return "";
   }
}

// Typhoon Scale
const char* QZQSM::dc12sr2str(int code)
{
   switch (code) {
   case 0: return "none";
   case 1: return "large";
   case 2: return "extremely large";
   case 15: return "other size classes";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Size classification (code number: %d)", code);
     return _undefMessage;
   }
}

// Typhoon Intensity
const char* QZQSM::dc12ic2str(int code)
{
   switch (code) {
   case 0: return "none";
   case 1: return "strong";
   case 2: return "very strong";
   case 3: return "Ferocious";
   case 15: return "other strength classes";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Strength class classification (code number: %d)", code);
     return _undefMessage;
   }
}

// Typhoon Intensity
const char* QZQSM::dc12w2str1(int w)
{
   static char wstr1[8];
   if (w == 0) {
     return "unknown";
   } else {
     snprintf(wstr1, sizeof(wstr1), "%d", w);
     return wstr1;
   }
}

const char* QZQSM::dc12w2str2(int w)
{
   static char wstr2[8];
   if (w == 0) {
     return "unknown";
   } else {
     snprintf(wstr2, sizeof(wstr2), "%d", w);
     return wstr2;
   }
}

int QZQSM::filter_dc12()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc12()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC12_REPORT, it2str(_Header.It), _jstAtMo, _jstAtD, _jstAtH, _jstAtMi);
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC12_REPORT2, _u.Dc12.Tn, _u.Dc12.BtD, _u.Dc12.BtH, _u.Dc12.BtM,
                   dc12dt2str(_u.Dc12.Dt), _u.Dc12.Du,
                   dc12sr2str(_u.Dc12.Sr), dc12ic2str(_u.Dc12.Ic),
                    _u.Dc12.LatNs ? "South" : "North", _u.Dc12.LatD, _u.Dc12.LatM, _u.Dc12.LatS,
                    _u.Dc12.LonEw ? "West longitude" : "East longitude", _u.Dc12.LonD, _u.Dc12.LonM, _u.Dc12.LonS,
                   _u.Dc12.Pr, dc12w2str1(_u.Dc12.W1), dc12w2str2(_u.Dc12.W2));
}

void QZQSM::decode_dc12()
{
  _u.Dc12.BtD   = get_val( 53, 5);
  _u.Dc12.BtH   = get_val( 58, 5);
  _u.Dc12.BtM   = get_val( 63, 6);
  _u.Dc12.Dt    = get_val( 69, 3);
  _u.Dc12.Du    = get_val( 80, 7);
  _u.Dc12.Tn    = get_val( 87, 7);
  _u.Dc12.Sr    = get_val( 94, 4);
  _u.Dc12.Ic    = get_val( 98, 4);
  _u.Dc12.LatNs = get_val(102, 1);
  _u.Dc12.LatD  = get_val(103, 7);
  _u.Dc12.LatM  = get_val(110, 6);
  _u.Dc12.LatS  = get_val(116, 6);
  _u.Dc12.LonEw = get_val(122, 1);
  _u.Dc12.LonD  = get_val(123, 8);
  _u.Dc12.LonM  = get_val(131, 6);
  _u.Dc12.LonS  = get_val(137, 6);
  _u.Dc12.Pr    = get_val(143, 11);
  _u.Dc12.W1    = get_val(154, 7);
  _u.Dc12.W2    = get_val(161, 7);
  utc2jst(_Header.AtMo, _u.Dc12.BtD, _u.Dc12.BtH, _u.Dc12.BtM);
}
#endif // QZQSM_ENABLE_DC12

#ifdef QZQSM_ENABLE_DC14
//===============================================================
// Disaster Category Code 14
// JMA-DC Report (Marine)

#define DC14_REPORT \
   "Disaster Report (Marine)(%s)\n\n" \
   "Announcement time: %d month %d day %d hour %d minute\n\n"

#define DC14_REPORT2 \
   "%s: %s\n"

// Warning Code (Region)
const char* QZQSM::dc14dw2str(int code)
{
   switch (code) {
   case 0: return "Maritime warning canceled";
   case 10: return "marine icing warning";
   case 11: return "marine heavy fog warning";
   case 12: return "Sea swell warning";
   case 20: return "marine wind warning";
   case 21: return "marine gale warning";
   case 22: return "marine storm warning";
   case 23: return "marine typhoon warning";
   case 31: return "other maritime alerts";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Maritime alert (code number: %d)", code);
     return _undefMessage;
   }
}

// Marine Forecast Region
const char* QZQSM::dc14pl2str(int code)
{
   switch (code) {
   case 1000: return "Northern Sea of Japan and Southern Okhotsk Northern Sea of Japan";
   case 1010: return "Sea East of Sakhalin";
   case 1020: return "Sea west of Sakhalin";
   case 1030: return "off Abashiri";
   case 1040: return "Soya Straits";
   case 1050: return "Hokkaido West Sea";
   case 1100: return "Hokkaido Southern and Eastern Seas";
   case 1110: return "Hokkaido Toho Marine";
   case 1120: return "off Kushiro";
   case 1130: return "off Hidaka";
   case 1140: return "Tsugaru Strait";
   case 1150: return "Hiyama off Tsugaru";
   case 2000: return "Off Sanriku";
   case 2010: return "East Sanriku";
   case 2020: return "West Sanriku";
   case 3000: return "Kanto area";
   case 3010: return "Northern Kanto area";
   case 3020: return "Southern Kanto area";
   case 3100: return "Central Sea of Japan";
   case 3110: return "Off Southern Primorye";
   case 3120: return "off Akita";
   case 3130: return "Off Sado";
   case 3140: return "off Noto";
   case 3200: return "Tokai area";
   case 3210: return "Eastern Tokai area";
   case 3220: return "West Tokai area";
   case 3230: return "Southern Tokai area";
   case 4000: return "Off Shikoku and Seto Inland Sea";
   case 4010: return "Seto Inland Sea";
   case 4020: return "Northern Shikoku";
   case 4030: return "Southern Shikoku";
   case 4100: return "Western Sea of Japan";
   case 4110: return "Northeast Japan Sea";
   case 4120: return "Eastern San'in and near Wakasa Bay";
   case 4130: return "San'in Oki West";
   case 5000: return "Tsushima Strait";
   case 5100: return "Kyushu West Sea";
   case 5110: return "Sea west of Jeju Island";
   case 5120: return "Nagasaki West Marine";
   case 5130: return "Mejima southwest sea";
   case 5200: return "Kyushu Southern Sea and Hyuga Sea";
   case 5210: return "Hyuganada";
   case 5220: return "Kagoshima Sea Area";
   case 5230: return "Amami area";
   case 6000: return "Okinawa waters";
   case 6010: return "Southern East China Sea";
   case 6020: return "Okinawa East Sea";
   case 6030: return "Okinawa Southern Sea";
   case 10000: return "Other Local Marine Forecast Areas";
   default:
     snprintf(_undefMessage, sizeof(_undefMessage),
              "Local Maritime Forecast Area (code number: %04d)", code);
     return _undefMessage;
   }
}

int QZQSM::filter_dc14()
{
  // You can filter out the specific region or information.
  return 1;
}

void QZQSM::report_dc14()
{
  _len += snprintf(&_message[_len], sizeof(_message) - _len,
                   DC14_REPORT, it2str(_Header.It), _jstAtMo, _jstAtD, _jstAtH, _jstAtMi);
  int num;
  for (num = 0; num < 8; num++) {
    if (_u.Dc14.site[num].Pl != 0) {
      _len += snprintf(&_message[_len], sizeof(_message) - _len,
                       DC14_REPORT2, dc14dw2str(_u.Dc14.site[num].Dw), dc14pl2str(_u.Dc14.site[num].Pl));
    }
  }
}

void QZQSM::decode_dc14()
{
  int num;
  for (num = 0; num < 8; num++) {
    _u.Dc14.site[num].Dw = get_val(53 + (19 * num), 5);
    _u.Dc14.site[num].Pl = get_val(58 + (19 * num), 14);
  }
}
#endif // QZQSM_ENABLE_DC14

// Information Type
const char* QZQSM::it2str(int code)
{
  switch (code) {
  case 0: return "Announcement";
  case 1: return "correction";
  case 2: return "cancel";
  default: return "";
  }
}

int QZQSM::get_val(int startbit, int bitwidth)
{
  int val = 0;
  int index = (startbit + bitwidth - 1) / 8;
  int lsb = 7 - (startbit + bitwidth - 1) % 8;

  int i;
  for (i = 0; i < bitwidth; i++, lsb++) {
    if (lsb > 7) {
      index -= 1;
      lsb = 0;
    }
    val |= ((_buf[index] >> lsb) & 1) << i;
  }
  return val;
}

void QZQSM::utc2jst(int& month, int& day, int& hour, int& minute)
{
  uint32_t sec;
  struct tm tm;

  tm.tm_sec  = 0;
  tm.tm_min  = minute;
  tm.tm_hour = hour;
  tm.tm_mday = day;
  tm.tm_mon  = month - 1;
  tm.tm_year = _year - 1900;
  sec = mktime(&tm);

  sec += (9 * 60 * 60); // UTC -> JST

  gmtime_r(&sec, &tm);

  _year = tm.tm_year + 1900;
  month = tm.tm_mon + 1;
  day = tm.tm_mday;
  hour = tm.tm_hour;
  minute = tm.tm_min;
}

//===============================================================
// Public Functions
//===============================================================

QZQSM::QZQSM() : _len(0)
{
  memset(_buf, 0, sizeof(_buf));
  memset(_message, 0, sizeof(_message));
}

QZQSM::~QZQSM()
{
}

QZQSM::QZQSM(const QZQSM &val)
{
  memcpy(_message, val._message, sizeof(_message));
  _len = val._len;
}

QZQSM& QZQSM::operator = (const QZQSM &rhs)
{
  memcpy(_message, rhs._message, sizeof(_message));
  _len = rhs._len;
  return *this;
}

bool QZQSM::operator == (const QZQSM &rhs)
{
  return (0 == strncmp(_message, rhs._message, sizeof(_message)));
}

bool QZQSM::operator != (const QZQSM &rhs)
{
  return (0 != strncmp(_message, rhs._message, sizeof(_message)));
}

void QZQSM::Decode(const char *nmea)
{
  uint8_t data[32];
  String str(nmea);

  int i;
  int n = 0;
  str.setCharAt(73,'0');
  for (i = 10; i < 74; i += 2) {
    String ch = str.substring(i, i + 2);
    data[n++] = strtoul(ch.c_str(), NULL, 16) & 0xff;
  }
  Decode(data);
}

void QZQSM::Decode(const uint8_t *data)
{
  memset(_buf, 0, sizeof(_buf));
  memset(_message, 0, sizeof(_message));
  _len = 0;

  memcpy(_buf, data, sizeof(_buf));

  _Header.PAB  = get_val( 0, 8);
  _Header.MT   = get_val( 8, 6);
  _Header.Rc   = get_val(14, 3);
  _Header.Dc   = get_val(17, 4);
  _Header.AtMo = get_val(21, 4);
  _Header.AtD  = get_val(25, 5);
  _Header.AtH  = get_val(30, 5);
  _Header.AtMi = get_val(35, 6);
  _Header.It   = get_val(41, 2);

  _jstAtMo = _Header.AtMo;
  _jstAtD  = _Header.AtD;
  _jstAtH  = _Header.AtH;
  _jstAtMi = _Header.AtMi;
  utc2jst(_jstAtMo, _jstAtD, _jstAtH, _jstAtMi);

  if (0 == (_category & (1 << _Header.Dc))) {
    return;
  }

  switch (_Header.Dc) {
#ifdef QZQSM_ENABLE_DC1
  case 1:
    decode_dc1();
    if (filter_dc1())
      report_dc1();
    break;
#endif
#ifdef QZQSM_ENABLE_DC2
  case 2:
    decode_dc2();
    if (filter_dc2())
      report_dc2();
    break;
#endif
#ifdef QZQSM_ENABLE_DC3
  case 3:
    decode_dc3();
    if (filter_dc3())
      report_dc3();
    break;
#endif
#ifdef QZQSM_ENABLE_DC4
  case 4:
    decode_dc4();
    if (filter_dc4())
      report_dc4();
    break;
#endif
#ifdef QZQSM_ENABLE_DC5
  case 5:
    decode_dc5();
    if (filter_dc5())
      report_dc5();
    break;
#endif
#ifdef QZQSM_ENABLE_DC6
  case 6:
    decode_dc6();
    if (filter_dc6())
      report_dc6();
    break;
#endif
#ifdef QZQSM_ENABLE_DC8
  case 8:
    decode_dc8();
    if (filter_dc8())
      report_dc8();
    break;
#endif
#ifdef QZQSM_ENABLE_DC9
  case 9:
    decode_dc9();
    if (filter_dc9())
      report_dc9();
    break;
#endif
#ifdef QZQSM_ENABLE_DC10
  case 10:
    decode_dc10();
    if (filter_dc10())
      report_dc10();
    break;
#endif
#ifdef QZQSM_ENABLE_DC11
  case 11:
    decode_dc11();
    if (filter_dc11())
      report_dc11();
    break;
#endif
#ifdef QZQSM_ENABLE_DC12
  case 12:
    decode_dc12();
    if (filter_dc12())
      report_dc12();
    break;
#endif
#ifdef QZQSM_ENABLE_DC14
  case 14:
    decode_dc14();
    if (filter_dc14())
      report_dc14();
    break;
#endif
  default:
    printf("Not Supported Category = %d\n", _Header.Dc);
    break;
  }
}

const char* QZQSM::GetReport()
{
  //printf("*** _len=%d\n", _len);
  return _message;
}

uint16_t QZQSM::_year = 2019;

void QZQSM::SetYear(int year)
{
  _year = year;
}

uint32_t QZQSM::_category = 0xffffffff;

void QZQSM::EnableCategory(int category)
{
  _category |= (1 << category);
}

void QZQSM::DisableCategory(int category)
{
  _category &= ~(1 << category);
}
