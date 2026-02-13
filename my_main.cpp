#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "13_1_10task.cpp"
// #include "my_task.cpp"
// #include "os_file.h"

using namespace std;

int main()
{

    // TEST 2
    file_manager_t fm;
    setup_file_manager(&fm);
    /* Common file manager test 1 */
    cout << (fm.create(1000) == 1) << endl; /* expected: 1 */
    cout << (fm.create_file("test_file",1000+1) == 0) << endl; /* expected: 0 */
    cout << (fm.destroy() == 1) << endl; /* expected: 1 */
    cout << (fm.destroy() == 0) << endl; /* expected: 0 */
    cout << (fm.create(1000) == 1) << endl; /* expected: 1 */
    cout << (fm.create(1000) == 0) << endl; /* expected: 0 */
    cout << (fm.destroy() == 1) << endl << endl; /* expected: 1 */

    cout << "----------------" << endl;

    /* Common file manager test 2 */
    cout << (fm.create(1000) == 1) << endl; /* expected: 1 */
    cout << (fm.create_file("file1.txt",1000) == 1) << endl; /* expected: 1 */
    cout << (fm.create_file("file2.txt",1) == 0) << endl; /* expected: 0 */
    cout << (fm.remove("file1.txt",0) == 1) << endl; /* expected: 1 */
    cout << (fm.remove("file1.txt",0) == 0) << endl; /* expected: 0 */
    cout << (fm.create_file("file2.txt",1000/2) == 1) << endl; /* expected: 1 */
    cout << (fm.create_file("file2.txt",1000/2) == 0) << endl; /* expected: 0 */
    cout << (fm.create_file("file3.txt",1000/2) == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("test_dir") == 1) << endl; /* expected: 1 */
    cout << (fm.remove("file2.txt",0) == 1) << endl; /* expected: 1 */
    cout << (fm.destroy() == 1) << endl << endl; /* expected: 1 */
    
    cout << "----------------" << endl;

    /* Common file manager test 3 */
    cout << (fm.create(1000) == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("dir1") == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("dir1/dir11") == 1) << endl; /* expected: 1 */
    cout << (fm.change_dir("dir1") == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("../dir2") == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("../dir2/dir3") == 1) << endl; /* expected: 1 */
    cout << (fm.remove("/dir2/dir3", 0) == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("/dir3/dir31") == 0) << endl; /* expected: 0 */
    cout << (fm.create_dir("../dir3/dir31") == 0) << endl; /* expected: 0 */
    cout << (fm.create_dir("../dir2") == 0) << endl; /* expected: 0 */
    cout << (fm.create_file("/dir2/file1", 1) == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("/dir2/dir21") == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("/dir2/file1") == 0) << endl; /* expected: 0 */
    cout << (fm.create_dir("../dir2/file1") == 0) << endl; /* expected: 0 */
    cout << (fm.create_dir("../dir2/file1/dir") == 0) << endl; /* expected: 0 */
    cout << (fm.create_dir("../dir2/dir22") == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("..") == 0) << endl; /* expected: 0 */
    cout << (fm.create_dir("../dir2/.") == 0) << endl; /* expected: 0 */
    cout << (fm.change_dir("dir2") == 0) << endl; /* expected: 0 */
    cout << (fm.change_dir("dir11") == 1) << endl; /* expected: 1 */
    cout << (fm.remove("../../dir2/file1", 0) == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("../../dir2/file1") == 1) << endl; /* expected: 1 */
    cout << (fm.remove("../../dir2/file1", 0) == 1) << endl; /* expected: 1 */
    cout << (fm.create_dir("../../dir2/file1") == 1) << endl; /* expected: 1 */
    cout << (fm.remove("../../dir2/file1", 0) == 1) << endl; /* expected: 1 */
    cout << (fm.create_file("../../dir2/file1", 1) == 1) << endl; /* expected: 1 */
    cout << (fm.change_dir(".") == 1) << endl; /* expected: 1 */
    cout << (fm.change_dir("/dir1/dir11") == 1) << endl; /* expected: 1 */
    cout << (fm.change_dir("/dir1/dir11/dir3") == 0) << endl; /* expected: 0 */
    cout << (fm.change_dir("/dir1") == 1) << endl; /* expected: 1 */
    cout << (fm.change_dir("./dir11") == 1) << endl; /* expected: 1 */
    cout << (fm.change_dir("..") == 1) << endl; /* expected: 1 */
    cout << (fm.create_file("ddir2/file1", 1000-1) == 0) << endl; /* expected: 0 */
    cout << (fm.create_file("./dir11/file.txt", 1) == 1) << endl; /* expected: 1 */
    fm.size("/");
    cout << (fm.remove("dir11", 0) == 0) << endl; /* expected: 0 */
    cout << (fm.remove("./dir11", 0) == 0) << endl; /* expected: 0 */
    cout << (fm.remove("./dir11", 1) == 1) << endl; /* expected: 1 */
    // fm.get_cur_dir(cur_dir)
    // strcmp(cur_dir,"/dir1") == 0 || strcmp(cur_dir, "/dir1/") == 0; /* expected: 1 */
    cout << (fm.destroy() == 1) << endl; /* expected: 1 */

      // // TEST 3
    // /* Test 1 */
    file_manager_t mm;
    setup_file_manager(&mm);


    mm.create(1000); /* expected: 1 */
    mm.create_dir("dir1"); /* expected: 1 */
    mm.create_dir("dir1/dir11"); /* expected: 1 */
    mm.change_dir("dir1"); /* expected: 1 */
    mm.create_dir("../dir2"); /* expected: 1 */
    mm.create_dir("../dir2/dir3"); /* expected: 1 */
    mm.remove("/dir2/dir3", 0); /* expected: 1 */
    mm.create_dir("/dir3/dir31"); /* expected: 0 */
    mm.create_dir("../dir3/dir31"); /* expected: 0 */
    mm.create_dir("../dir2"); /* expected: 0 */
    mm.create_file("/dir2/file1", 1); /* expected: 1 */
    mm.create_dir("/dir2/dir21"); /* expected: 1 */
    mm.create_dir("/dir2/file1"); /* expected: 0 */
    mm.create_dir("../dir2/file1"); /* expected: 0 */
    mm.create_dir("../dir2/file1/dir"); /* expected: 0 */
    mm.create_dir("../dir2/dir22"); /* expected: 1 */
    mm.change_dir("dir2"); /* expected: 0 */
    mm.change_dir("dir11"); /* expected: 1 */
    mm.remove("../../dir2/file1", 0); /* expected: 1 */
    mm.create_dir("../../dir2/file1"); /* expected: 1 */
    mm.remove("../../dir2/file1", 0); /* expected: 1 */
    mm.create_file("../../dir2/file1", 1); /* expected: 1 */
    mm.change_dir("."); /* expected: 1 */
    mm.change_dir("/dir1/dir11"); /* expected: 1 */
    mm.change_dir("/dir1/dir11/dir3"); /* expected: 0 */
    mm.change_dir("/dir1"); /* expected: 1 */
    mm.change_dir("./dir11"); /* expected: 1 */
    mm.change_dir(".."); /* expected: 1 */
    mm.create_file("./dir11/file.txt", 1); /* expected: 1 */
    mm.remove("dir11", 0); /* expected: 0 */
    mm.remove("./dir11", 0); /* expected: 0 */
    mm.remove("./dir11", 1); /* expected: 1 */
    // mm.list("..",0); /* expected: 1 */
    // mm.list("dir1",0); /* expected: 0 */
    // mm.list(".",0); /* expected: 1 */
    // mm.list("./dir11/file.txt",0); /* expected: 0 */
    mm.create_file("file11.txt",1); /* expected: 1 */
    // mm.list("./file11.txt",0); /* expected: 1 */
    // mm.list("file11.txt",0); /* expected: 1 */
    mm.create_file("../dir2/a_file22.txt",1); /* expected: 1 */
    // mm.list("../dir2",0); /* expected: 1 */
    // mm.list("../dir2",1); /* expected: 1 */
    // mm.list("../dir1 ../dir2",1); /* expected: 1 */
    // mm.list("../dir2 ../dir3",1); /* expected: 0 */
    mm.destroy(); /* expected: 1 */

    // Create(10);
    // create_dir((char *)"/dir1");
    // create_dir((char *)"/dir1/dir2");
    // create_dir((char *)"/dir1/dir2/dir3");
    // create_file((char *)"/dir1/dir2/", 10);
    // change_dir((char*)"/dir1");
    // change_dir((char*)"/");
    // // recursive_list((char*)"/",0);

    // create_dir("/a");
    // create_dir("/a1");
    // create_dir("/b");
    // create_dir("/b/1");
    // create_dir("/b/1/1");
    // create_dir("/b/a");
    // create_dir("/c");
    // // recursive_list((char*)"/",0);
    // destroy();

   
}