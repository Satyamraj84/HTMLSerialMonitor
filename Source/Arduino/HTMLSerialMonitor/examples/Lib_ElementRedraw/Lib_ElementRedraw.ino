/*
  Lib_ElementRedraw.ino   - Sample sketch part of HTMLSerialMonitor package
                            Demonstrates framework of library and shows that
                            modify only element properties will allow for 
                            fast animation/updates. 
  created:  26 May 2016
  version:  29 May 2016
  author :  Nard Janssens
  license:  Attribution-NonCommercial-ShareAlike 2.5 Generic (CC BY-NC-SA 2.5)
*/

#include <HTMLSerialMonitor.h>
HTMLSerialMonitor SerialM;
int frameNr=0;

void setup(){
    SerialM.begin(9600);
    
    //We setup the gui and start by clearing the page with [cls] 
    SerialM.println("[cls]");

    //nice page title
    SerialM.print("<h1>Sample - Element Redraw (fast) </h1><hr>");

    //section title for DIGITAL pins
    SerialM.print("<br><br><b>Digital Pins:</b><br>");

    //header: add table row with column headers (pin labels)
    SerialM.print("<table style='text-align:center'>");
    SerialM.print("<tr style='font-size:10px;'>");      
    for (int i=2;i<14;i++){ 
      SerialM.print("<th>"+String(i)+"</th>");
    }
    SerialM.print("</tr>");

    //table value cells where each cell gets an unique id to reference in the loop and change its value/properties
    SerialM.print("<tr>");    
    for (int i=2;i<14;i++){
      SerialM.print("<td id='D"+String(i)+"' style='border:1px solid black;width:2em;'>0</td>");
      pinMode(i,INPUT);
    }
    SerialM.print("</tr></table>");
    
    //section title for ANALOG pins
    SerialM.print("<br><br><br><b>Analog Pins:</b><br>");

    //header: add table row with column headers (pin labels)
    SerialM.print("<table style='text-align:center'>");
    SerialM.print("<tr style='font-size:10px;'>");      
    for (int i=1;i<6;i++){ 
      SerialM.print("<th>"+String(i)+"</th>");  
    }
    SerialM.print("</tr>");

    //table value cells where each cell gets an unique id to reference in the loop and change its value/properties
    SerialM.print("<tr>");      
    for (int i=1;i<6;i++){
      SerialM.print("<td style='border:1px solid black;width:50px;'>");
      SerialM.print("<div id='A"+String(i)+"' style='background-color:yellow'></div></td>");
      pinMode(i,INPUT);
    }    
    SerialM.print("</tr></table>");

    //count nr of frames
    SerialM.print("<br><br>frameNr:<span id='frameNr'>0</span>");

    //close print string to let monitor proces it
    SerialM.println("");
}

void loop(){
  //increment frameNr
  frameNr++;
  String fr="[frameNr:"+String(frameNr)+"]";
  SerialM.print(fr);
  
  //modify text and color of table cells for digital pins
  for (int i=2;i<14;i++){    
    String id="D"+String(i);    
    //first we set innerHTML of element (td) with id: D2..D14
    int iVal=digitalRead(i);
    String val=String(iVal);
    String cmd1="["+id+":"+val+"]";
    SerialM.print(cmd1);
    //next we set background color depending on value of D2..D14
    String prop=".b";    
    String color="";
    if (iVal==1) color="green";    
    if (iVal==0) color="red";    
    String cmd2="["+id+prop+":"+color+"]";    
    SerialM.print(cmd2);
  }
  
  //modify text and barwidth within table cells for analog pins
  for (int i=1;i<6;i++){    
    String id="A"+String(i);    
    int iVal=analogRead(i);    
    String val=String(iVal);
    String cmd1="["+id+":"+val+"]";
    SerialM.print(cmd1);
    String prop=".w";  
    String perc=String(50*iVal/1024)+"px";    
    String cmd2="["+id+prop+":"+perc+"]";        
    SerialM.print(cmd2);    
  }    

  //close print string to let monitor proces it    
  SerialM.println("");

  //we call hndlRemoteCmd to enable the control buttons (play/reset) at the top right of the monitor
  SerialM.hndlRemoteCmd(); //or call serialEvent if you need the input yourself
}

/*
//If you use SerialEvent to intercept messages you need to 
//use the available and read method from the HTMLSerialMonitor library 
String inputString="";
void serialEvent() {
  while (SerialM.available()) {
      char inChar=(char) SerialM.read();
      inputString += inChar;
      if (inChar == '\n') { 
        Serial.println("Received:"+inputString.substring(0,inputString.length()-1)+"|");
        inputString="";
      }          
  }
}*/
