#include "CalcTask.h"




void CalcTask::run()
{
	float temp = 0;
	temp = (loop / total) * 100;
   // int perc = temp; // conv to int for function

   // if (temp%5 == 0)
  //  {
        std::cout << std::setprecision(2);
        std::cout << "\r" << temp << "% complete                                               " << "\r";
        //std::cout << temp << "% complete    " << "\n";
  //  }
  /*  else
    {
        return;
    }
	*/

}
