// Test the motors angular velocity and produce an output file

#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <stopwatch.h>
#include <robot_delay.h>
#include <bitset>
#include <string>
#include "robot_initialise.h"

int main () {
  initialise_robot();

  // Parameters for the test
  const int max_cmd_speed = 127; // int corresponding to max speed cmd
  const int num_test_speeds = 10; // Number of different speeds to test
  // int num_tests = 2; // Number of tests per speed
  const float test_time = 5000; // Duration in seconds of each test
  int motor_cmd_speeds[num_test_speeds];
  float angular_speeds[num_test_speeds];

  // The readings at cmd_speed = 0 will yield 0 angular speeds.
  motor_cmd_speeds[0] = 0;
  angular_speeds[0] = 0.0;

  // Uniformly divide the motor_cmd_speeds onto the range 0 - 127
  for (int i = 1; i < num_test_speeds; i++) {
    // Set the cmd speed for this test
    int cmd_speed = (i * max_cmd_speed) / num_test_speeds;

    // Prompt the user to make sure he has equipment set up for the test
    string user_response;
    while (user_response != "yes"):
      cout << "> Are you ready to continue testing? (Enter 'yes'): " << endl;
      cin >>  user_response;

    cout << "Test " << i << " out of " << num_test_speeds << " initiating." << endl;
    cout << "Motor command speed is: " << cmd_speed << endl;

    rlink.command(MOTOR_1_GO, cmd_speed); //Initiate the motor movement
    delay(test_time);

    // Let the user input test results:
    int n_rotations;
    int n_degrees_over;
    cout << "Enter the number of FULL ROTATIONS of the wheel: " << endl;
    cin >> n_rotations;
    cout << "Enter the number of degrees extra the wheel has turned after "
    << n_rotations << " full rotations: " << endl;
    cin >> n_degrees_over;
    // Conver to rpm
    float rpm = (float(n_rotations)+float(n_degrees_over)/360.0) / (test_time / 60000);
    // Enter results into arrays
    motor_cmd_speeds[i] = cmd_speed;
    angular_speeds[i] = rpm;

  }

  // Write the results to a file
  ofstream fout;
  fout.open("motor_speed_test_results.txt");
  if (fout) { // file opened successfully
    for (int i = 0; i < num_test_speeds; i = i ++) {
      fout << motor_cmd_speeds[i] << ’ ’ << angular_speeds[i] << endl;
    }
  } else { // file did not open successfully
    cout << "Could not open text file for writing. Print to cout instead" << endl;
    // Instead, print results to terminal so that all is not lost
    for (int i = 0; i < num_test_speeds; i = i ++) {
      cout << motor_cmd_speeds[i] << ’ ’ << angular_speeds[i] << endl;
    }
  }

  return 0;
}