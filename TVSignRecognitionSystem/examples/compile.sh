g++ train.cpp -o TRAIN ../lib/libtvSign.a `pkg-config --cflags --libs opencv` -lboost_filesystem-mt
g++ match.cpp -o MATCH ../lib/libtvSign.a `pkg-config --cflags --libs opencv` -lboost_filesystem-mt
g++ matchdir.cpp -o MATCHDIR ../lib/libtvSign.a `pkg-config --cflags --libs opencv` -lboost_filesystem-mt
g++ test.cpp -o TEST ../lib/libtvSign.a `pkg-config --cflags --libs opencv` -lboost_filesystem-mt
g++ test_a_picture.cpp -o TEST_A_PICTURE ../lib/libtvSign.a `pkg-config --cflags --libs opencv` -lboost_filesystem-mt
