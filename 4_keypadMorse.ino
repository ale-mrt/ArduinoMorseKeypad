#include <Keypad.h>

//these are all the variables that code every letter in morse code: 1 is short, 2 is long
String a = "12";String b = "211";String c = "2121";String d = "211";String e = "1";String f = "1121";String g = "221";
String h = "1111";String i = "11";String j = "1222";String k = "212";String l = "1211";String m = "22";String n = "21";
String o = "222";String p = "1221";String q = "2212";String r = "121";String s = "111";String t = "2";String u = "112";
String v = "1112";String w = "122";String x = "2112";String y = "2122";String z = "2211";String zero = "22222";
String one = "12222";String two = "11222";String three = "11122";String four = "11112";String five = "11111";
String six = "21111";String seven = "22111";String eight = "22211";String nine = "22221";
const byte ROWS = 4;  //rows of the keypad
const byte COLS = 4;  //columns of the keypad
//this matrix contains all the symbols of the keypad
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {49, 48, 47, 46}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {45, 44, 43, 42}; //connect to the column pinouts of the keypad
//instantiating the keypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
String phrase;  //this string will contain the t9 strokes phrase
String decoded; //this string will contain the human-readable phrase

//this function takes in the string that represents duration of the letters: 1 is short (dot), 2 is long (line)
void lightUp(String letter){
  int pnt;  //loop counter
  
  //this loop iterates over the string passed to the function with pnt
  for(pnt = 0; pnt < letter.length(); pnt++){
    //the program lights up the LED for 200 ms if the duration is short (1), 400 ms if the duration is long (2)
    if(letter[pnt] == '1'){
      digitalWrite(LED_BUILTIN, true);
      delay(200);
      digitalWrite(LED_BUILTIN, false);
      delay(200);
    }else if(letter[pnt] == '2'){
      digitalWrite(LED_BUILTIN, true);
      delay(500);
      digitalWrite(LED_BUILTIN, false);
      delay(200);
    }else{
      Serial.print("lightUp: error, no 1 or 2 detected\n");
    }
  }
  delay(800);
}

//this function converts every letter of the decoded phrase in morse code
void lightUpPhrase(String decodedPhrase){
  int pnt, intLetter; //loop counter and the ASCII code for the char
  
  //this loop iterates over the decodedPhrase with pnt
  for(pnt = 0; pnt < decodedPhrase.length(); pnt++){
    //if there's a space intLetter is set to -1
    if(decodedPhrase[pnt] == ' '){
      intLetter = -1;
    }else{
      //the program converts the letter pointed by pnt to the respective ASCII code
      intLetter = int(decodedPhrase[pnt]);
    }
    //this switch-case calls for the lightUp function depending on the character's ASCII code
    switch(intLetter){
      case 97:        lightUp(a);      break;
      case 98:        lightUp(b);      break;
      case 99:        lightUp(c);      break;
      case 100:        lightUp(d);      break;
      case 101:        lightUp(e);      break;
      case 102:        lightUp(f);      break;
      case 103:        lightUp(g);      break;
      case 104:        lightUp(h);      break;
      case 105:        lightUp(i);      break;
      case 106:        lightUp(j);      break;
      case 107:        lightUp(k);      break;
      case 108:        lightUp(l);      break;
      case 109:        lightUp(m);      break;
      case 110:        lightUp(n);      break;
      case 111:        lightUp(o);      break;
      case 112:        lightUp(p);      break;
      case 113:        lightUp(q);      break;
      case 114:        lightUp(r);      break;
      case 115:        lightUp(s);      break;
      case 116:        lightUp(t);      break;
      case 117:        lightUp(u);      break;
      case 118:        lightUp(v);      break;
      case 119:        lightUp(w);      break;
      case 120:        lightUp(x);      break;
      case 121:        lightUp(y);      break;
      case 122:        lightUp(z);      break;
      case 48:        lightUp(zero);      break;
      case 49:        lightUp(one);      break;
      case 50:        lightUp(two);      break;
      case 51:        lightUp(three);      break;
      case 52:        lightUp(four);      break;
      case 53:        lightUp(five);      break;
      case 54:        lightUp(six);      break;
      case 55:        lightUp(seven);      break;
      case 56:        lightUp(eight);      break;
      case 57:        lightUp(nine);      break;
      case -1:        delay(1000);      break;
      default:        Serial.print("lightUpPhrase: char " + String(intLetter) + " not recognized\n"); break;
    } //switch selection end
  } //for loop end
}

//this function translates the t9 strokes into a human-readable string
String decodePhrase(String rawPhrase){
  String decodedPhrase, singleChar; //phrase that's going to be passed to the lightup function and the singleChar holder
  char currChar, prevChar;          //current and previous char pointed while decoding the t9 phrase
  int newChar = false;              //newWord boolean
  int pnt;                          //loop counter 

  //initializing strings and chars
  decodedPhrase = singleChar = "";
  currChar = prevChar = ' ';

  //if the phrase is an empty string I return the function with an empty string
  if(rawPhrase.equals("")){
    return decodedPhrase;
  }

  //if the end of the phrase isn't terminated then I add an hash symbol
  if(rawPhrase[rawPhrase.length() -1] != '#'){
    rawPhrase += "#";
  }

  //loop over the t9 phrase
  for(pnt = 0; pnt < rawPhrase.length(); pnt++){
    //if pnt is 0 then pnt is pointing at the first char of the phrase: I set the previous char is the same as the current
    if(pnt == 0 || prevChar == '#'){
      currChar = rawPhrase[pnt];
      prevChar = currChar;
      singleChar += currChar;
    //if pnt > 0 then pntr points at some point of a phrase
    }else{
      currChar = rawPhrase[pnt];
      //it the current char is an hash then there's a space, aka a new word
      if(currChar == '#'){
        newChar = true;
        prevChar = currChar;
      //if the current char differs from the previous one, then a new human-readable char is starting
      }else if(currChar != prevChar){
        newChar = true;
        prevChar = currChar;
      //if currChar == prevChar then the t9 char continues
      }else{
        singleChar += currChar;
        prevChar = currChar;
      }
    }

    //if newChar is true then the t9 letter contained in singleChar is completed
    if(newChar == true){
      //for every t9 combination I add the corresponding char to the decoded string
      if(singleChar.equals("2")){
        decodedPhrase += "a";
      }else if(singleChar.equals("22")){
        decodedPhrase += "b";
      }else if(singleChar.equals("222")){
        decodedPhrase += "c";
      }else if(singleChar.equals("3")){
        decodedPhrase += "d";
      }else if(singleChar.equals("33")){
        decodedPhrase += "e";
      }else if(singleChar.equals("333")){
        decodedPhrase += "f";
      }else if(singleChar.equals("4")){
        decodedPhrase += "g";
      }else if(singleChar.equals("44")){
        decodedPhrase += "h";
      }else if(singleChar.equals("444")){
        decodedPhrase += "i";
      }else if(singleChar.equals("5")){
        decodedPhrase += "j";
      }else if(singleChar.equals("55")){
        decodedPhrase += "k";
      }else if(singleChar.equals("555")){
        decodedPhrase += "l";
      }else if(singleChar.equals("6")){
        decodedPhrase += "m";
      }else if(singleChar.equals("66")){
        decodedPhrase += "n";
      }else if(singleChar.equals("666")){
        decodedPhrase += "o";
      }else if(singleChar.equals("7")){
        decodedPhrase += "p";
      }else if(singleChar.equals("77")){
        decodedPhrase += "q";
      }else if(singleChar.equals("777")){
        decodedPhrase += "r";
      }else if(singleChar.equals("7777")){
        decodedPhrase += "s";
      }else if(singleChar.equals("8")){
        decodedPhrase += "t";
      }else if(singleChar.equals("88")){
        decodedPhrase += "u";
      }else if(singleChar.equals("888")){
        decodedPhrase += "v";
      }else if(singleChar.equals("9")){
        decodedPhrase += "w";
      }else if(singleChar.equals("99")){
        decodedPhrase += "x";
      }else if(singleChar.equals("999")){
        decodedPhrase += "y";
      }else if(singleChar.equals("9999")){
        decodedPhrase += "z";
      }else if(singleChar.equals("0")){
        decodedPhrase += "0";
      }else if(singleChar.equals("1")){
        decodedPhrase += "1";
      }else if(singleChar.equals("2222")){
        decodedPhrase += "2";
      }else if(singleChar.equals("3333")){
        decodedPhrase += "3";
      }else if(singleChar.equals("4444")){
        decodedPhrase += "4";
      }else if(singleChar.equals("5555")){
        decodedPhrase += "5";
      }else if(singleChar.equals("6666")){
        decodedPhrase += "6";
      }else if(singleChar.equals("77777")){
        decodedPhrase += "7";
      }else if(singleChar.equals("8888")){
        decodedPhrase += "8";
      }else if(singleChar.equals("99999")){
        decodedPhrase += "9";
      }else{
        Serial.print("error in t9 char recognition\n");
      }
      //after adding the char to the final string, I reset newChar to false and I set singleChar to an empty string
      newChar = false;
      singleChar = "";
      //if the last seen char wasn't an hash, then I add the previous char in the singleChar string, if not I add a space to the decoded phrase
      if(prevChar != '#'){
        singleChar += prevChar;
      }else{
        decodedPhrase += " ";
      }
    }
  }

  return decodedPhrase;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if(customKey){
    //A prints the raw t9 phrase
    if(customKey == 'A'){
      Serial.print("raw phrase = " + phrase + "\n");
    //B prints the decoded phrase
    }else if(customKey == 'B'){
      Serial.print("decoded phrase = " + decoded + "\n");
    //C cancels the decoded and raw phrases
    }else if(customKey == 'C'){
      Serial.print("wiped out previous phrase\n");
      phrase = "";
      decoded = "";
    //D decodes the t9 phrase into a human-readable phrase and passes the string to the function that blinks in morse code
    }else if(customKey == 'D'){
      //decoding the t9 phrase into a human-readable phrase
      decoded = decodePhrase(phrase);
      Serial.print("blinking " + decoded + "\n");
      //repeating the phrase in morse code
      lightUpPhrase(decoded);
      Serial.print("done blinking " + decoded + "\n");
    // * does nothing
    }else if(customKey == '*'){
      Serial.print("unused key\n");
    }else{
      if(phrase.length() >= 100){
        Serial.println("Max phrase count reached");
      }else{
        Serial.println(customKey);
        phrase+= customKey;
      }
    }
  }
}
