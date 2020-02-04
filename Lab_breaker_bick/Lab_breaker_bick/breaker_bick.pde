
/////////////////VARIABLES7777777777

float px, py, bx, by, b_velocidad_x, b_velocidad_y, direccion;
int p_ancho, p_alto, b_tam, w, h, capas;
boolean  inicio;
ArrayList bloques;
import controlP5.*;
import processing.serial.*;
Serial port;
int valor=0;

//////////////////////////////////////////////////
void setup() {

  size(800, 600);
  smooth(2);

  px = width/2;
  py = height-20;
  p_ancho = 100;
  p_alto = 15;

  bx = width/2;
  by = height/2;
  b_tam = 20;
  b_velocidad_x = 0;
  b_velocidad_y = 0;
  inicio = false;
  w = width/10;
  h = 20;
  capas = 4;
  direccion = 0; 


  ////////////ARDUINO/////
  port=new Serial(this, "COM4", 9600);


  background(255);
  bloques = new ArrayList();

  for (int tx = 0; tx <= 9; tx++) {
    for (int ty = 0; ty <= capas-1; ty++) {
      bloques.add(new Brick(tx*w+w/2, ty*h+h/2, ceil(random(4))));
    }
  }
}

void draw() {
  background(0);
  inicio();
  perdedor(); 
  ganador();
  paleta();
  bola();
  control_golpe();
  control_bola_paleta();


  for (int i = bloques.size()-1; i >= 0; i--) {
    Brick onebrick = (Brick) bloques.get(i);
    onebrick.display();
    if (onebrick.collision(bx, by, b_tam)) {
      b_velocidad_y *= -1;
      bloques.remove(i);
    }
  }
}

void paleta() {  

  if (port.available()>0) { 
    valor = (port.read())*80;
  }
  fill(255);
  rectMode(CENTER);
  rect(valor, py, p_ancho, p_alto);
}

void bola() {
  bx += b_velocidad_x;
  by += b_velocidad_y;

  fill(255);
  ellipse(bx, by, b_tam, b_tam);
}

void control_bola_paleta() {
  if (bx > px-p_ancho/2 && bx < valor+p_ancho/2 && by+ b_tam/3 > py-p_alto) {
    b_velocidad_y *= -1;

    if (bx > valor) {
      direccion = (dist(bx, by+ b_tam/2, valor, py-p_alto/2))*-1;
    }
    if (bx < valor) {
      direccion = dist(bx, by+ b_tam/2, valor, py-p_alto/2);
    }

    b_velocidad_x = direccion/10;
  }
}

void control_golpe() {
  if (bx+ b_tam/2 > width || bx- b_tam/2 < 0) {
    b_velocidad_x *= -1;
  }
  if (by- b_tam/2 < 0) {
    b_velocidad_y *= -1;
  }
}


class Brick {
  float x, y;
  int w, h;
  int c;

  Brick(float X, float Y, int C) {
    x = X;
    y = Y;
    c = C;

    w = width/10;
    h = 20;
  }

  void display() {
    if (c == 1) {
      fill(#FF0303);
    }
    if (c == 2) {
      fill(#FFF703);
    }
    if (c == 3) {
      fill(#03FF04);
    }
    if (c == 4) {
      fill(#0A03FF);
    }
    rect(x, y, w, h);
  }

  boolean collision(float Bx, float By, float Bsize) {
    if ((bx+ b_tam/2 > x-w/2) &&
      (bx- b_tam/2 < x+w/2) &&
      (by- b_tam/2 < y+h/2) &&
      (by+ b_tam/2 > y-h/2)) {
      return(true);
    } else {
      return(false);
    }
  }
}


void inicio() {
  if (keyPressed && inicio == false) {
    if ( key == ENTER || key == RETURN) {
      b_velocidad_y = 4;
      inicio = true;
    }
  }
}


void ganador() {
  if (bloques.size() == 0 && capas == 1) {
    background(0);
    b_velocidad_x = 0;
    b_velocidad_y = 0;
    textAlign(CENTER);
    textSize(40);
    fill(255);   
    text("GANASTE!", width/2, height/2+40);
    noLoop();
  }
}

void perdedor() {
  if (bloques.size() == 0) {
    b_velocidad_x = 0;
    b_velocidad_y = 0;
    textAlign(CENTER);
    textSize(40);
    fill(255);
    text("PERDISTE!!", width/2, height/2);
  }
  if (by+ b_tam/2 > height) {
    b_velocidad_x = 0;
    b_velocidad_y = 0;
    textAlign(CENTER);
    textSize(40);
    fill(255);
    text("PERDISTE!!", width/2, height/2);
  }
}
