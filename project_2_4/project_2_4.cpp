#include <iostream> // Gives us access to std::cin and std::cout
#include <string>   // Gives us access to std::string and std::getline()

struct LightOutputs
{
  bool red_ns;
  bool yellow_ns;
  bool green_ns;
  bool red_ew;
  bool yellow_ew;
  bool green_ew;
};

struct LightInputs
{
  int time;
  bool car_sensor_n;
  bool car_sensor_s;
};

// TODO Define your light controller state machine class here
LightOutputs out;
LightInputs in;

bool noCarsNS(LightInputs in)
{
  return in.car_sensor_n && in.car_sensor_s;
}

bool bothRed(LightOutputs out)
{
  return out.red_ew && out.red_ns;
}

int main()
{
  // TODO Initialize your state machine class here
  out.red_ns = 1;
  out.yellow_ns = 0;
  out.green_ns = 0;

  out.red_ew = 1;
  out.yellow_ew = 0;
  out.green_ew = 0;

  in.time = 0;

  while (true)
  {
    std::string input;
    std::getline(std::cin, input);
    if (input.size() != 2)
      break;

    // TODO Parse the input digits
    in.car_sensor_n = std::stoi(input.substr(0, 1));
    in.car_sensor_s = std::stoi(input.substr(1, 1));

    // TODO Update your state machine based on input
    if (bothRed(out))
    {
      // if both red
      if (in.time < 1)
      {
        // if both red and not yet one second, do nothing
      }
      else
      {
        // if been one second, change to green
        in.time = 0;
        if (noCarsNS)
        {
          out.red_ew = 0;
          out.green_ew = 1;
        }
        else
        {
          out.red_ns = 0;
          out.green_ns = 1;
        }
      }
    }
    else if (out.red_ew)
    {
      // if NS is moving
      if (out.yellow_ns)
      {
        // if NS is yellow
        if (in.time < 2)
        {
          // do nothing
        }
        else
        {
          out.yellow_ns = 0;
          out.red_ns = 1;
          in.time = 0;
        }
      }
      else
      {
        // if NS is green
        if (in.time < 5)
        {
          // do nothing
        }
        else
        {
          out.green_ns = 0;
          out.yellow_ns = 1;
          in.time = 0;
        }
      }
    }
    else
    {
      // if EW is moving
      if (out.yellow_ew)
      {
        // if EW is yellow
        if (in.time < 2)
        {
          // do nothing
        }
        else
        {
          out.yellow_ew = 0;
          out.red_ew = 1;
          in.time = 0;
        }
      }
      else
      {
        // if EW is green
        if (in.time < 5)
        {
          // do nothing
        }
        else
        {
          out.green_ew = 0;
          out.yellow_ew = 1;
          in.time = 0;
        }
      }
    }

    in.time++;

    // TODO Output your state machine's light controls to std::cout
    std::cout << out.red_ns << out.yellow_ns << out.green_ns << out.red_ew << out.yellow_ew << out.green_ew << std::endl;
  }
  return 0;
}
