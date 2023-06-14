#include "systemc.h"
#include "fifo_if.h"
// I declare size here as im confused at how  
// to declare an array in private variables
// as we do not know the size yet

template <class T> class fifo: public sc_module, public fifo_out_if <T>, public fifo_in_if <T>
{
  private: 
    T* data;
    int size;

    int free;        // Free space
    int ri;         // Read Index
    int wi;         // Write Index

    bool read_flag;
    bool write_flag;
    bool read_status;
    bool write_status;

    T write_T;
    T* read_T;

    sc_event read_req;//data_read_event;
    sc_event write_req; //data_written_event;
    sc_event done; 

  public:
    // Constructor size???
      SC_HAS_PROCESS(fifo);
      fifo(sc_module_name nm, int size_) : sc_module(nm)
      { 
        size = size_;
        free = size; 
        data = new T[size];
        ri = 0;
        wi = 0;

        read_flag = false;
        write_flag = false; 
        read_status = false; 
        write_status = false;

        SC_THREAD(arbitrator);
        sensitive << read_req << write_req; //dont_initialize(); 

      }

    void arbitrator(){

      while(1){
        //cout << "in arbitrator" << endl;

        if (read_flag){ // Read flag highest prio
          read_flag = false;

          if(free < size){ // fifo not empty 
            *read_T = data[ri]; // read from data
            ri = (ri + 1) % size; //increase read index
            free++; // FIFO availability increased by one
            read_status = true;

          } 
          else read_status = false; 
          }


        if(write_flag){
          write_flag = false; 

          if (free > 0){ // Make sure fifo is not full
            
            data[wi] = write_T; // write to data
            wi = (wi + 1) % size; //increase write index
            free--; // fifo availability reduced by one
            write_status = true;

          } 
          else write_status = false;
          }

        done.notify();
        wait(); 
      }
    }


    bool write(T data)
    {
      write_flag = true;
      write_T = data;
      write_req.notify();
      wait(done);
      return write_status;
    }

    bool read(T& data)
    {
      read_flag = true;
      read_T = &data;
      read_req.notify();
      wait(done);
      return read_status; 
    }
};

