// Go until first intersection and align with it (axis over intersection)

#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include "robot_initialise.h"
#include "line_following.h"
#include "components.h"

int main () {
  initialise_robot();
  cout << "Running test line following forwards and bakcwards." << endl;

  int pcb1_port = 0; // Port number for PCB 1
  int pcb2_port = 1; // Port number for PCB 2

  Components components(pcb1_port, pcb2_port);
  Line_Following lf(components);

  // Set parameters for the test
  float speed = 1.0; // Set speed of motors in range 0-1
  float ramp =  0;// Set acceleration of motors in range 0-254
  lf.set_ramp(ramp);

  float speed_delta = 0.5;
  int num_intersections_to_ignore = 0;
  bool keep_driving_after_last = true; // Decides whether to stop motors when the final intersection is reached

  lf.follow_line(speed, speed_delta,
              num_intersections_to_ignore, keep_driving_after_last);
  lf.align_with_intersection(speed, speed_delta);
  lf.reverse_until_switch(speed, 0.5)

  cout << "Finished" << endl;

  return 1;
}
