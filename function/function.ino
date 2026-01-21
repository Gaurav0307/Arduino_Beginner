void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float length;
  float width;
  float area;
  float perimeter;
  float diagonal;

  Serial.print("Enter Length: ");
  while(Serial.available()==0);
  length = Serial.parseFloat();
  Serial.println(length);

  Serial.print("Enter Width: ");
  while(Serial.available()==0);
  width = Serial.parseFloat();
  Serial.println(width);

  // area = findArea(length, width);
  // Serial.println("Area = " + String(area));

  // perimeter = findPerimeter(length, width);
  // Serial.println("Perimeter = " + String(perimeter));

  // diagonal = findDiagonal(length, width);
  // Serial.println("Diagonal = " + String(diagonal));

  findArea(length, width, area);
  Serial.println("Area = " + String(area));

  findPerimeter(length, width, perimeter);
  Serial.println("Perimeter = " + String(perimeter));

  findDiagonal(length, width, diagonal);
  Serial.println("Diagonal = " + String(diagonal));
}

// float findArea(float l, float w) {
//   float a;
//   a=l*w;
//   return a;
// }

// float findPerimeter(float l, float w) {
//   float p;
//   p=l*2 + w*2;
//   return p;
// }

// float findDiagonal(float l, float w) {
//   float d;
//   d=sqrt(l*l + w*w);
//   return d;
// }

void findArea(float l, float w, float &a) {
  a=l*w;
}

void findPerimeter(float l, float w, float &p) {
  p=l*2 + w*2;
}

void findDiagonal(float l, float w, float &d) {
  d=sqrt(l*l + w*w);
}
