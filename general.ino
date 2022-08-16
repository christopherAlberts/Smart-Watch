


// interrupt service routine
void senseButtonPressed1() {
    if (!isButtonPressed1) {
        isButtonPressed1 = true;
    }
}

void senseButtonPressed2() {
    if (!isButtonPressed2) {
        isButtonPressed2 = true;
    }
}

void senseButtonPressed3() {
    if (!isButtonPressed3) {
        isButtonPressed3 = true;
    }
}

void senseButtonPressed4() {
    if (!isButtonPressed4) {
        isButtonPressed4 = true;
    }
}



void next_page(){
  Serial.println(sizeof(pages));
   if(currentPage < (sizeof(pages)/sizeof(pages[0]))-1){
    currentPage++;
  }
  else{
    currentPage = 0;
  }
   //Change page
    if(currentPage == 0){
      Serial.println("You are on page 1");
      page1();
    }
    else if (currentPage == 1){
      Serial.println("You are on page 2");
      page2_wifi();
    }
    else if (currentPage == 2){
      Serial.println("You are on page 3");
      page3();
    }
    else if (currentPage == 3){
      Serial.println("You are on page 4");
      page4();
    }
    else{
      Serial.println("ERROR: currentPage DOES NOT EXIST!");
      digitalWrite(NEOPIXEL_POWER, LOW);
    }

  Serial.print("currentPage: ");
  Serial.println(currentPage);

  
}

void previos_page(){
  if(currentPage > 0){
    currentPage--;
  }
  else{
    currentPage = (sizeof(pages)/sizeof(pages[0]))-1;
  }
  
  //Change page
    if(currentPage == 0){
      Serial.println("You are on page 1");
      page1();
    }
    else if (currentPage == 1){
      Serial.println("You are on page 2");
      page2_wifi();
    }
    else if (currentPage == 2){
      Serial.println("You are on page 3");
      page3();
    }
    else if (currentPage == 3){
      Serial.println("You are on page 4");
      page4();
    }
    else{
      Serial.println("ERROR: currentPage DOES NOT EXIST!");
      digitalWrite(NEOPIXEL_POWER, LOW);
    }

  Serial.print("currentPage: ");
  Serial.println(currentPage);
}
