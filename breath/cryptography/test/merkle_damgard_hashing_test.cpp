// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "breath/counting/count.hpp"
#include "breath/temp_testing/test.hpp"


#include "breath/cryptography/digest.hpp"
// gps #include "breeze/cryptography/digest_io.hpp"
#include "breath/cryptography/md5_hasher.hpp"
#include "breath/cryptography/sha1_hasher.hpp"
#include "breath/cryptography/sha256_hasher.hpp"
#include "breath/cryptography/sha224_hasher.hpp"
#include "breath/cryptography/sha512_hasher.hpp"

#include <string>
#include <sstream>
#include <iostream> // gps temp
#include <cstddef>

// Questo non � ovviamente un test automatico.
// Ma � gi� qualcosa :-) gps

namespace {

    const std::string::size_type million( 1000 * 1000 );
    const std::string one_million_a( million, 'a' );

    template< typename Hasher >
    class test_vectors
    {
    public:
        struct test_entry
        {
            std::string source;
            std::string expected;
            std::size_t repetitions;
        };

        static test_entry const entries[];
    };

    // MD5 test vectors ---------------------------------------------------- //

    template<>
    const test_vectors< breath::md5_hasher >::test_entry
        test_vectors< breath::md5_hasher >::entries[] =
    {
        // test cases from RFC 1321
        {                           "" ,  "d41d8cd98f00b204e9800998ecf8427e" },
        {                          "a" ,  "0cc175b9c0f1b6a831c399e269772661" },
        {                        "abc" ,  "900150983cd24fb0d6963f7d28e17f72" },
        {             "message digest" ,  "f96b697d7cb7938d525a2f31aaf161d0" },
        { "abcdefghijklmnopqrstuvwxyz" ,  "c3fcd3d76192e4007dfb496cca67e13b" },

        { "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          "abcdefghijklmnopqrstuvwxyz"
                          "0123456789" ,  "d174ab98d277d9f5a5611c2c9f419d9f" },

        { "12345678901234567890123456"
          "78901234567890123456789012"
          "34567890123456789012345678"
                                  "90" ,  "57edf4a22be3c955ac49da2e2107b67a" },

        // other test cases
        {                     "Breeze" ,  "a35715e7a6549f47dc766f75a0b1088c" },

        { "The quick brown fox jumps "
                   "over the lazy dog" ,  "9e107d9d372bb6826bd81d3542a419d6" },

        { "The quick brown fox jumps "
                   "over the lazy cog" ,  "1055d3e698d289f2af8663725127bd4b" },

        // 56 byte (= 448 bit) message
        { "01234567890123456789012345"
          "67890123456789012345678901"
          "2345"                       ,  "8af270b2847610e742b0791b53648c09" },

        // 57-byte
        { "01234567890123456789012345"
          "67890123456789012345678901"
          "23456"                      ,  "c620bace4cde41bc45a14cfa62ee3487" },

        // 64-byte
        { "01234567890123456789012345"
          "67890123456789012345678901"
          "234567890123"               ,  "7f7bfd348709deeaace19e3f535f8c54" }

    };


    // SHA-1 test vectors -------------------------------------------------- //

    template<>
    const test_vectors< breath::sha1_hasher >::test_entry
        test_vectors< breath::sha1_hasher >::entries[] =
    {
        // test cases from FIPS 180-2 with change notice
        { "abc", "a9993e364706816aba3e25717850c26c9cd0d89d"},

        { "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
          "84983e441c3bd26ebaae4aa1f95129e5e54670f1" },
        { one_million_a,
          "34aa973cd4c4daa4f61eeb2bdbad27316534016f" },

        //{ std::string( 1ul << 29, 'a' ),
        //}

        // gps { "a", "34aa973cd4c4daa4f61eeb2bdbad27316534016f" },

        // the usual "crazy cog" :-)
        { "The quick brown fox jumps over the lazy cog",
          "de9f2c7fd25e1b3afad3e85a0bd17d9b100db4b3" }
    };

    // SHA-256 test vectors ------------------------------------------------ //

    template<>
    const test_vectors< breath::sha256_hasher >::test_entry
        test_vectors< breath::sha256_hasher >::entries[] =
    {
        // test cases from FIPS
        { "abc",
          "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad" },
        { "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
          "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1" },
        { one_million_a,
          "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0" },

        // others

        // 2^(10+19) = 2^29 bytes = 2^32 bits
        { std::string( 1ul << 10, 'a' ),
          "b9045a713caed5dff3d3b783e98d1ce5778d8bc331ee4119d707072312af06a7",
          ( 1ul << 19 ) - 1 }
    };

    // SHA-224 test vectors ------------------------------------------------ //

    template<>
    const test_vectors< breath::sha224_hasher >::test_entry
        test_vectors< breath::sha224_hasher >::entries[] =
    {
        // from FIPS
        { "abc",
          "23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7" }
    };


    // SHA-512 test vectors ------------------------------------------------ //
    template<>
    const test_vectors< breath::sha512_hasher >::test_entry
        test_vectors< breath::sha512_hasher >::entries[] =
    {
        // from FIPS
        { "abc",
          "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a"
          "2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f" },

        { "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
          "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",

          "8e959b75dae313da8cf4f72814fc143f8f7779c6eb9f7fa17299aeadb6889018"
          "501d289e4900f7e4331b99dec4b5433ac7d329eeb6dd26545e96e55b874be909" },

        { one_million_a,
          "e718483d0ce769644e2e42c7bc15b4638e1f98b13b2044285632a803afa973eb"
          "de0ff244877ea60a4cb0432ce577c31beb009c5c2c49aa2e4eadb217ad8cc09b"}
    };

}


// Smoke test - Check against a list of known digests
//
template< typename Hasher >
void check_known_digests()
{
    typedef std::string string_type;
    typedef test_vectors< Hasher > known;

    for ( std::size_t i( 0 ); i < breath::count( known::entries ); ++i ) {

        using breath::digest;

        const typename known::test_entry & entry( known::entries[ i ] );
        const string_type & src( entry.source );

        Hasher hasher( src.begin(), src.end() );
        //Hasher hasher;

        // repetitions?
        for ( std::size_t r( 0 ); r < /*1 + */entry.repetitions; ++r ) {
            hasher.append( src.begin(), src.end() );
        }

        const digest< Hasher > d( hasher );
        std::stringstream stream;
        stream << d;
        std::string result;
        stream >> result;
        BREATH_CHECK( result /*== GPS CHANGEd TEMPrarly*/ == entry.expected );

    }

}



//{
//    std::cout << "Tests for cv-filter (da spostare...)\n";
//    //std::cout << "unsigned of char = " << typeid( breeze::meta::unsigned_of<const char>::type ).name() << '\n';
//
//    // gps da spostare
//    BREEZE_STATIC_ASSERT( (breeze::meta::is_same<
//        breeze::meta::unsigned_of< volatile char >::type,
//        volatile unsigned char
//                          >::value), "" );
//}

//#include "breeze/testing/test_error.hpp"
//#include "breeze/testing/test_descriptor.hpp"
void gimme_false()
{
    //BREEZE_CHECK( false ) ; // intentional failure
    breeze::check( false, "intentional failure", BREEZE_SOURCE_LOCUS ) ;
   
}

int main()
{
#if 0
    using breeze::test_runner ;

    test_runner & runner = test_runner::instance() ;

    breeze::test_descriptor descs[] =
    {
        check_known_digests< breeze::   md5_hasher > ,
        check_known_digests< breeze::  sha1_hasher > ,
        check_known_digests< breeze::sha256_hasher > ,
        check_known_digests< breeze::sha224_hasher > ,
        check_known_digests< breeze::sha512_hasher >
    } ;
#endif

    try {
        //breeze::test_group group( "Known digests", descs ) ;    
        /*       group
        .add(
        check_known_digests< breeze::   md5_hasher > )
        .add(
        check_known_digests< breeze::  sha1_hasher > )
        .add(
        check_known_digests< breeze::sha256_hasher > )
        .add(
        check_known_digests< breeze::sha224_hasher > )
        .add(
        check_known_digests< breeze::sha512_hasher > )
        ;*/

        /*
        breeze::test_reporter reporter( std::cout ) ;
        runner.attach( reporter ) ;
        //run.add( group ) ;
        runner.run();
        */

        breeze::test_descriptor funcs[] =
    {
        breeze::test_descriptor( gimme_false, "dummy function" ),
        check_known_digests< breath::   md5_hasher > ,
        check_known_digests< breath::  sha1_hasher > ,
        check_known_digests< breath::sha256_hasher > ,
        check_known_digests< breath::sha224_hasher > ,
        check_known_digests< breath::sha512_hasher >
    } ;


        breath::test_group group( breeze::begin( funcs ), breeze::end( funcs ) ) ;
        breath::run_unit_tests() ;

    } catch ( std::exception & ex ) {
        //std::cout << "OK! Got exception from the hasher!!!\n";
        std::cout << "Exception while adding tests..." << std::endl ;
        std::cout << "--> " << ex.what() << std::endl;
    }

 
    //// gps Another test --- should go to another file??

    ////2^64
    //static const char fb[] = "/_\\|*";
    //int pos = 0;

    //std::string s = "abcdefghijklmnopqrstuvwxyz" ;
    //for( int i = 0; i < 15; ++i )
    //    s += s;


    //try {


    //for( std::size_t a = 0; a < (1ul << 16); ++ a ){
    //for( std::size_t b = 0; b < (1ul << 16); ++ b )
    //for ( std::size_t i = 0; i < (1ul << 16); ++ i ) {
    //    for ( std::size_t k = 0; k < (1ul << 16); ++ k ) {
    //        for (std::size_t m = 0; m < 8; ++m ) {
    //            breeze::sha1_hasher h;
    //            h.append( s.begin(), s.end() );
    //        }
    //        std::cout << '\r' << fb[ pos ] ;
    //        pos = ( pos + 1 ) % sizeof fb ; 

    //    }
    //    std::cout << "i = " << i << std::endl;
    //}
    //std::cout << a << "\n";
    //}

    //}
    //catch ( breeze::hashing_count::exception & ) {
    //    std::cout << "OK! Got exception from the hasher!!!\n";
    //}
    //catch( std::length_error & )
    //{
    //    std::cout << std::endl;
    //    std::cout << "Sorry, string threw :-(\n";
    //
    //} 
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
