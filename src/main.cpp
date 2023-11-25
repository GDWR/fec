#include <iostream>
#include <vector>

class Emulator {
  int memory[8];
  char counter;
  char instruction;
  char accumulator;

public:
  void load(std::vector<char> programBinary) {
    std::copy(programBinary.begin(), programBinary.end(), this->memory);
  }

  void cycle() {
    fetch();
    execute();
  }

  void fetch() {
    this->instruction = this->memory[this->counter];
    this->counter++;
  }

  void execute() {
    if (this->instruction == 0x16) {
      accumulator = memory[6];
    } else if (this->instruction == 0x27) {
      accumulator += memory[7];
    } else if (this->instruction == 0x36) {
      this->memory[6] = accumulator;
    } else if (this->instruction == 0x41) {
      this->counter = 0;
    }
  }

  char get_memory(int address) { return this->memory[address]; }
  char get_instruction() { return this->instruction; }
  char get_accumulator() { return this->accumulator; }
  char get_counter() { return this->counter; }
};

int main(int argc, char *argv[]) {
  Emulator *emulator = new Emulator();
  int program[8] = {0x16, 0x27, 0x36, 0x41, 0x00, 0x00, 0x1, 0x1};
  emulator->load(std::vector<char>(program, program + 8));

  while (true) {
    std::cout << "Press enter to cycle, press q then enter to quit. ";
    if (std::cin.get() == 'q') {
      break;
    }

    emulator->cycle();
    std::cout << "counter: " << std::hex << (int)emulator->get_counter() << std::endl;
    std::cout << "instruction: " << std::hex << (int)emulator->get_instruction() << std::endl;
    std::cout << "accumulator: " << std::hex << (int)emulator->get_accumulator() << std::endl;
    std::cout << "address 6: " << emulator->get_memory(6) << std::endl;
    std::cout << std::endl;
  }

  return 0;
}
