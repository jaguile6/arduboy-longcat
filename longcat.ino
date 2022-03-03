#include <Arduboy2.h>
Arduboy2 arduboy;
#include "maps.h"
#include "images.h"

uint8_t current[] = {
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000
};

int8_t GRID_SIZE = 8;
int8_t heroX;
int8_t heroY;
int8_t heroVX;
int8_t heroVY;
int8_t stage = 0;
int8_t stages;

void setup() {
  arduboy.boot();
  arduboy.setFrameRate(30);
  arduboy.clear();
  arduboy.drawBitmap(15,0,cat,27,64);
  arduboy.setCursor(45,30);
  arduboy.println("LongCat");
  arduboy.setCursor(45,45);
  arduboy.println("Press A");
  arduboy.display();
  arduboy.delayShort(2000);
  while (!arduboy.pressed(A_BUTTON)) {
    
  }
  initLevel();
  
}

void nextStage(){
  arduboy.setCursor(70,30);
  arduboy.print("Perfect!");
  arduboy.display();
  arduboy.delayShort(1000);
  arduboy.clear();
  stage = stage + 1;
  initLevel();
}

void endGame(){
  arduboy.clear();
  arduboy.setCursor(10,30);
  arduboy.print("Game Completed!");
  arduboy.display();
  arduboy.delayShort(3000);
  stage = 0;
  initLevel();
}

void loop() {
  if(!arduboy.nextFrame()){
    return;
  }
  readButtons();
  move();
  renderHero();
  arduboy.display();
  if(checkWin()){
    if(stage==45){
      endGame();
    }else{
      nextStage();
    }
  }
}

void initLevel(){
  heroVX = 0;
  heroVY = 0;
  heroX = 3;
  heroY = 3;
  fillSquare(heroX,heroY);
  arduboy.clear();
  copyLevel();
  drawLevel();
  renderHero();
  printLevel();
}

void printLevel(){
  arduboy.setCursor(70,20);
  arduboy.print("LVL: ");
  arduboy.print(stage+1);
  arduboy.setCursor(70,50);
  arduboy.print("B: Retry");
}

bool copyLevel(){
  for(int i=0; i<8; i++){
    //current[i]=levels[stage][i];
    current[i]=pgm_read_byte_near(levels[stage]+i);
  }
  heroX = pgm_read_byte_near(levels[stage]+8);
  heroY = pgm_read_byte_near(levels[stage]+9);
}

void drawLevel(){
  for(int j=0;j<8;j++){
    for(int i=0;i<8;i++){
      if(squareCheck(i,j)){
        arduboy.fillRect(i*GRID_SIZE, j*GRID_SIZE, GRID_SIZE, GRID_SIZE ,1);
      }else{
        arduboy.drawPixel(i*GRID_SIZE+3, j*GRID_SIZE+3, 1);
      }
    }
  }
}

void move(){
  int nextX = constrain(heroX+heroVX, 0, 7);
  int nextY = constrain(heroY+heroVY, 0, 7);
  if( !squareCheck( nextX , nextY ) ){
    arduboy.fillRect(heroX*GRID_SIZE+2,heroY*GRID_SIZE+2,4,4,0);
    heroX =  nextX;
    heroY =  nextY;
    //drawHero(heroX, heroY, GRID_SIZE);
    fillSquare(heroX,heroY);
  }
}
void renderHero(){
  drawHero(heroX*GRID_SIZE,heroY*GRID_SIZE,GRID_SIZE);
}
void drawHero(int x, int y, int size){
  arduboy.drawRect(x+1, y+1, size-2, size-2 ,1);
  //arduboy.drawRect(x+2, y+2, size-4, size-4 ,1);
  arduboy.drawPixel(x+3, y+3, 1);
  arduboy.drawPixel(x+5, y+3, 1);
}

void fillSquare(int x, int y){
  bitWrite(current[y], 7-x, 1);
}
bool squareCheck(int8_t x, int8_t y){
  return bitRead(current[y],7-x);
}

bool checkWin(){
  for(int i=0;i<8;i++){
    if(current[i]!=0b11111111){
      return false;
    }
  }
  return true;
}

void readButtons(){
  if (arduboy.pressed(UP_BUTTON)) {
    heroVX=0;
    heroVY=-1;
  }
  else if (arduboy.pressed(RIGHT_BUTTON)) {
    heroVX=1;
    heroVY=0;
  }
  else if (arduboy.pressed(DOWN_BUTTON)) {
    heroVX=0;
    heroVY=1;
  }
  else if (arduboy.pressed(LEFT_BUTTON)) {
    heroVX=-1;
    heroVY=0;
  }
  if (arduboy.pressed(B_BUTTON)) {
    initLevel();
  }
  if (arduboy.pressed(A_BUTTON)) {
    //nextStage();
  }
}
