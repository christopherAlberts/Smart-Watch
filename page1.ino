
void page1(){
  currentPage = 0;
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(4);
  tft.println("Page 1!");
  tft.setCursor(0, 0); 

  Serial.print("currentPage: ");
  Serial.println(currentPage);
}
