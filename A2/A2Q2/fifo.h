#include "systemc.h"
#include "fifo_if.h"

class fifo
: public sc_prim_channel, public fifo_out_if,
  public fifo_in_if
{
protected:
  int size;                 // size
  char* buf;                // fifo buffer
  int free;                 // free space
  int ri;                   // read index
  int wi;                   // write index
  int num_readable;
  int num_read;
  int num_written;

  sc_event data_read_event;
  sc_event data_written_event;

public:
  // constructor
  fifo (const char* nm, int size_ = 16)
  : sc_prim_channel(nm)
  {
    size = size_;
    buf = new char[size];
    reset();
  }

  ~fifo()                   //destructor
  {
    delete [] buf;
  }


  int num_available() const
  {
    return num_readable - num_read;
  }

  int num_free() const
  {
    return size - num_readable - num_written;
  }


  void write(char c)        // blocking write
  {
    if (num_free() == 0) wait(data_read_event);
    num_written++;
    buf[wi] = c;
    wi = (wi + 1) % size;
    free--;
    request_update();
  }


  void reset()
  {
    free = size;
    ri = 0;
    wi = 0;
    num_readable = size - free;
    num_read = 0;
    num_written = 0;
  }


  void read(char& c)        // blocking read
  {
    if (num_available() == 0) wait(data_written_event);
    num_read++;
    c = buf[ri];
    ri = (ri + 1) % size;
    free++;
    request_update();
  }


  void update()
  {
    if (num_read > 0) data_read_event.notify(0, SC_NS);
    if (num_written > 0) data_written_event.notify(0, SC_NS);
    num_readable = size - free;
    num_read = 0;
    num_written = 0;
  }
};