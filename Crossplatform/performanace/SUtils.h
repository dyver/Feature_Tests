//!
//! Вывод отладочной информации
//!

#include <iostream>
#include <fstream>

#define DEBUG_DESTINATION_COUT 0
#define DEBUG_DESTINATION_CERR 1
#define DEBUG_DESTINATION_FILE 2

#ifndef DEBUG_LEVEL
	#warning SUtils` Logger will not output any data. \
			Define DEBUG_LEVEL with values between 0 and 3
	#define DEBUG_LEVEL 0
#endif

#ifndef DEBUG_OUT_DESTINATION
	#warning SUtils` Logger will output data to std::cout. \
			Define DEBUG_OUT_DESTINATION with value \
			equal to 0 (cout), 1 (cerr), or 2 (file)
#endif

#ifndef DEBUG_OUT_FILE_NAME
	#if DEBUG_OUT_DESTINATION == DEBUG_DESTINATION_FILE
		#warning SUtils` Logger will output data to /tmp/debug.txt. \
				Define DEBUG_DESTINATION_FILE to override this behavour.
		#define DEBUG_OUT_FILE_NAME /tmp/debug.txt
	#endif
#endif

#define MAKE_STRING(str) #str

namespace SUtils
{
	namespace Logger
	{
		struct CoutCreator {
			static std::ostream * create() { return &std::cout; }
		};
		struct CerrCreator {
			static std::ostream * create() { return &std::cerr; }
		};
		struct FileCreator {
			static std::ostream * create() { return new std::ofstream(MAKE_STRING(DEBUG_OUT_FILE_NAME)); }
		};
		#if DEBUG_OUT_DESTINATION == DEBUG_DESTINATION_COUT
			typedef CoutCreator destination;
		#elif DEBUG_OUT_DESTINATION == DEBUG_DESTINATION_CERR
			typedef CerrCreator destination;
		#elif DEBUG_OUT_DESTINATION == DEBUG_DESTINATION_FILE
			typedef FileCreator destination;
		#endif
		template<int level, class Policy = CoutCreator> class Dumper
		{
			#define criterion level <= DEBUG_LEVEL
			private:
				std::ostream *stream;
			public:
				typedef std::ostream &(&ostream_manipulator)(std::ostream &);
				typedef std::ios &(&ios_manipulator)(std::ios &);
				Dumper() {
					if (criterion)
						stream = Policy::create();
					else
						stream = 0;
				}
				template<class T> Dumper &operator <<(const T &data) {
					if (criterion)
						(*stream) << data;
					return *this;
				}
				Dumper &operator <<(ostream_manipulator man) {
					if (criterion)
						man(*stream);
					return *this;
				}
				Dumper &operator <<(ios_manipulator man) {
					if (criterion)
						man(*stream);
					return *this;
				}
			#undef criterion
		};
	}
}

extern SUtils::Logger::Dumper<1, SUtils::Logger::destination> d1cout;
extern SUtils::Logger::Dumper<2, SUtils::Logger::destination> d2cout;
extern SUtils::Logger::Dumper<3, SUtils::Logger::destination> d3cout;

#define _COUT( x ) \
		d1cout << " " << __FILE__ << ": (" << __LINE__ << ")\t" << x << std::endl

