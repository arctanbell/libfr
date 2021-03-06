#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <libfr.h>

#include <QApplication>
#include <QWidget>

#include <gtest/gtest.h>

namespace fr {
	namespace app {
        class AppDemo : public BaseApp
		{
        public:
            static const unsigned short DEFAULT_WINDOW_WIDTH = 250;
            static const unsigned short DEFAULT_WINDOW_HEIGHT = 150;
            static const char* DEFAULT_WINDOW_TITLE;

        public:
            /* virtual */ void InitOptions()
            {
                // Init parent options
                BaseApp::InitOptions();

                // Specify program options
                Opts.add_options()
                    ("gui,g", "show gui")
                    ("test,t", "run test")
                    ;
            }

            /* virtual */ int Run(int argc, const char** argv)
            {
                // You are right. This is overriden just for educational purposes.
                return BaseApp::Run(argc, argv);
            }

            /* virtual */ int ProcessOptions()
            {
                // GUI
                if(Args.count("gui"))
                {
                    QApplication app(Argc, const_cast<char**>(Argv));

                    QWidget window;

                    window.resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
                    window.setWindowTitle("Demo");
                    window.show();

                    return app.exec();
                }

                // Test app if requested
                if(Args.count("test"))
                {
                    std::cout << "Running the test." << std::endl;
                    // Tests that the Foo::Bar() method does Abc.

                    Test();

                    return EXIT_SUCCESS;
                }

                // If no arguments were specified print help and exit
                if(Argc < 1)
                {
                    PrintHelpMessage();
                    return EXIT_FAILURE;
                }

                // Print help and exit if needed
                if (Args.size() < 1)
                {
                    std::cout << Opts << std::endl;
                    return EXIT_SUCCESS;
                }

                // Let base process it ...
                return BaseApp::ProcessOptions();
            }

        private:
            void Test()
            {
                // ASSERT_TRUE(true);
            }
		}; // AppDemo
    } // namespace app
} // namespace fr

int main(int argc, const char** argv)
{
    // See http://www.zetcode.com/gui/qt4/firstprograms/
    return fr::app::AppDemo().Run(argc, argv);
}
