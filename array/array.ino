int items[20];
int numOfItems = 0;
int sum = 0;
float avg = 0.0;
int smallest;
int greatest;
int swap = 0;
int flap;

const int BAUD = 9600;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Enter number of items : ");
  while(Serial.available() == 0);
  numOfItems = Serial.parseInt();
  Serial.println(numOfItems);

  for(int i = 0; i < numOfItems; i++) {
    Serial.print("Enter item["+ String(i + 1) +"] : ");
    while(Serial.available() == 0);
    items[i] = Serial.parseInt();
    Serial.println(items[i]);
  }

  Serial.print("Items : ");
  for(int i = 0; i < numOfItems; i++) {
    Serial.print(String(items[i]) + " ");
  }

  sum = 0;
  smallest = greatest = items[0];

  for(int i = 0; i < numOfItems; i++) {
    if(smallest > items[i]) {
      smallest = items[i];
    }

    if(greatest < items[i]) {
      greatest = items[i];
    }

    sum+=items[i];
  }

  avg = float(sum) / numOfItems;

  Serial.println();
  Serial.println("Smallest : " + String(smallest));
  Serial.println("Greatest : " + String(greatest));
  Serial.println("Average : " + String(avg));

  // Ascending order
  // for(int i= 0; i < numOfItems-1; i++) {
  //   for(int j = i + 1; j < numOfItems; j++) {
  //     if(items[i] > items[j]) {
  //       swap = items[i];
  //       items[i] = items[j];
  //       items[j] = swap;
  //     }
  //   }
  // }

  // Ascending order (another way)
  flap = 1;
  while(flap == 1) {
    flap = 0;

    for(int i= 0; i < numOfItems-1; i++) {
      if(items[i] > items[i + 1]) {
        swap = items[i];
        items[i] = items[i + 1];
        items[i + 1] = swap;

        flap = 1;
      }
    }
  }

  Serial.print("Ascending Order : ");
  for(int i = 0; i < numOfItems; i++) {
    Serial.print(String(items[i]) + " ");
  }

  // Descending order
  // for(int i= 0; i < numOfItems-1; i++) {
  //   for(int j = i + 1; j < numOfItems; j++) {
  //     if(items[i] < items[j]) {
  //       swap = items[i];
  //       items[i] = items[j];
  //       items[j] = swap;
  //     }
  //   }
  // }

  // Descending order (another way)
  flap = 1;
  while(flap == 1) {
    flap = 0;

    for(int i= 0; i < numOfItems-1; i++) {
      if(items[i] < items[i + 1]) {
        swap = items[i];
        items[i] = items[i + 1];
        items[i + 1] = swap;

        flap = 1;
      }
    }
  }

  Serial.println();
  Serial.print("Descending Order : ");
  for(int i = 0; i < numOfItems; i++) {
    Serial.print(String(items[i]) + " ");
  }

  Serial.println();

  delay(100);
}
