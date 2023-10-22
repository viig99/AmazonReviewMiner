#include <catch2/catch_test_macros.hpp>
#include <YAKE.h>

TEST_CASE( "YAKE works as expected.", "[keyword_extraction]" ) {
    std::string sentence = "The only thing we have to fear is fear itself.";
    YAKE yake(sentence);
}