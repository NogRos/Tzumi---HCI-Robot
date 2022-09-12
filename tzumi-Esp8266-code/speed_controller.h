

int speeds[] = {3, 10, 14, 20, 18};                        //speeds (stop , slow , fast)
int speed_index = 0;                         //index for next speed array (circle)
int SIZE_OF_SPEED_LIST = sizeof(speeds) / sizeof(speeds[0]); //length of array
int SPINNING = 0;
int kick_for_tzumi = 3;

/*
//updates speed index circularly
void updateIndex(int sumButtons) {
  //speed_index = (speed_index + 1) % SIZE_OF_SPEED_LIST;
  speed_index = sumButtons % SIZE_OF_SPEED_LIST;
}
*/
