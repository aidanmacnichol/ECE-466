//Partial code example for producer "producer.h":

//...

template <class T> class producer : public sc_module 
{
public:
  sc_port < fifo_out_if<T> > out;
  sc_in_clk Clock; 

  void do_writes()
  {
    T data = 0;
    int i = 0; //I added this i the fuck would i use T for 
    //HMMMM so we need to specify size at construct so maybe use T here and thats how we know to redo
    while (true) 
    {
      wait();  
      if (out->write(data)) 
        cout << "W " << /*data cant i just use an int?*/ i << " at " << sc_time_stamp() << endl;
        i = (i+1) % 10; 
    }
  }

  SC_CTOR(producer)
  {
  SC_THREAD(do_writes);
  sensitive << Clock.pos();
  }
};

