// Go until second intersection and align with it (axis over intersection), turn around, repeat

#include <iostream>
#include <string>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <delay.h>
#include "robot_initialise.h"
#include "line_following.h"
#include "components.h"
#include "Robot.h"

int main () {

  int starting_direction = 90;
  char starting_junction = 'j';

  Robot robot(starting_junction, starting_direction);
  int num_repeat = 20;
  cout << "Running Alignment for pickup test" << endl;

  for (int i = 0; i < num_repeat; i++) {
    robot.align_for_pickup();
    delay(1000);
    robot.move('i');
    robot.move('j');
  }
}
