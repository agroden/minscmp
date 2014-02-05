#include "runnable.h"
#include "bozorth.h"

namespace minscmp {
	class minscmp_thread : public boilerplate::runnable {
	public:
		minscmp_thread();
		~minscmp_thread();
		
		void run();
	
	private:
		
	};

}