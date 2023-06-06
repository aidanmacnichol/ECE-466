//Partial code example for consumer "consumer.h":

//...

template <class T> class consumer : public sc_module 
{
public:
  sc_port < fifo_in_if<T> > in;
  sc_in_clk Clock;
  
  void do_reads()
  {
    T data;
    int i = 0; 
    while (true) 
    {
        wait();
      //DO MORE HERE
      //HM so we need to specify size at construct so maybe use T here and thats how we know to redo
      
      if (in->read(data)) 
        cout << "R " << data << " at " << sc_time_stamp() << endl;
	
//      ...
    }
  } 
  
//...