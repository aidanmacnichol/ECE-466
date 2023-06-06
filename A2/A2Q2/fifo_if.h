#include "systemc.h"

class fifo_out_if :  virtual public sc_interface
{
public:
  virtual void write(char) = 0;          // blocking write
  virtual int num_free() const = 0;      // free entries
};

class fifo_in_if :  virtual public sc_interface
{
public:
  virtual void read(char&) = 0;          // blocking read
  virtual int num_available() const = 0; // available entries
};
