echo("Hello from Test.cs");
// exec("./test2.cs");

function rl(%mode) {
    exec("./test.cs");

    if (%mode !$= "") {
        $mode = %mode;
        $i = $times = 0;
    }
}


// benchmark
$foo = new TestObj() {
    TypeF32 bar = 0.0;
    pointSize = LOOP_COUNT;
};


// $foo.dump();

function setMy() {
    %foo = $foo;
    %foo.myFloat = 2.2;
}



#define LOOP_COUNT 50000

$mode = -1;

function SpeedTest() {
    %lF32 = 0.0;
    %lS32 = 0;

    //  --- count up a member without TYPEDEF ---
    // .. object as global var
    if ( $mode == 0 ) {
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
            // $foo.bar += 0.1;
        }
    }
    else
    // .. object as local var
    if ( $mode == 1 ) {
        %foo = $foo;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
            %foo.bar += 0.1;
        }
    }
    else
    // .. object as local var + typed
    if ( $mode == 2 ) {
        %foo = $foo;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
            //NOTE Why is + - slower than * / ??

            // %foo.myFloat = 0.1; // 65ms
            // %foo.myFloat += 0.1; // 90ms
            // %foo.myFloat *= 0.1; //70ms
            // %foo.myFloat /= 0.1; //70ms
            // %foo.myFloat -= 0.1; //90ms
            %foo.myFloat =  %foo.myFloat * 0.1; //86ms
        }
    }
    // ------ working on engine defined properties --------
    else
    // .. object as local var + set X
    // NOTE: OMG is this slow !!!!!!!
    if ( $mode == 3 ) {
        %foo = $foo;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
            // THIS MUST BE A BUG !!! .x is slow like hell while myFloat is ok
            // -- x,y,z,w,r,g,b,a are defined in parser ---
            // 600 ms for this .... omg
            // %foo.x += 0.1; //NOTE VERY VERY SLOW

            // BUG testFloat is 600ms!!!
            // so its not the .x
            // %foo.testFloat *=   0.1;

            //NOTE Verified its not my ELFSCRIPT_STRICT_SLOT_TYPE

            // %testFloat = %foo.testFloat; //alone 60ms
            // %testFloat *= 0.1;
            // // !!!!!!!!!!!!1 THIS IT IS !!!!!!!!!!!!!!!!!!!!
            // %foo.testFloat = 4.2;

           // all three 87
            %foo.testFloat += 0.1; // 67 ms now !!!

            // %bar = %foo.testFloat * 1.001;
            // %foo.testFloat = %bar;
            //
            // if (%bar > 10000.0) %foo.testFloat = 0.0;
           //if ($i % 3 == 0)  echo(%foo.testFloat);

        }
    }
    else
    // .. object as local var + call walk
    if ( $mode == 4 ) {
        %foo = $foo;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
            %foo.walk(0.1, 0.4, 0.2); //NOTE FAST! 50-60ms
             // %foo.walk(0.1 * 1, 0.4 * 1, 0.2 * 1); //same speed with type casting
        }
    }
    else
    // .. object as local var + call getPos to a local var
    if ( $mode == 5 ) {
        %foo = $foo;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
            %posVec = %foo.getPos(); //not bad 111ms
        }
    }
    else
     // .. object as local var + call getx/y/z to a local vars
    if ( $mode == 6 ) {
        %foo = $foo;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
            // NOTE a bit slower than getPos: 122ms
            %x = %foo.getX();
            %foo.testFloat = %x;
            // %y = %foo.getY();
            // %z = %foo.getZ();
        }
    }
    else
    if ($mode == 7) {
        $foo.testFloat += 0.1415  ;
        %a = $foo.testFloat;
        %a *= 1.001;
        $foo.testFloat = %a;
        // echo($foo.x);
    }
    else
    if ($mode == 8) {
        // $foo.testInt++;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
             // $foo.testInt += 1;
             // $foo.testInt = 1; //50ms
             $foo.testInt = 1 * 1.0; // also 50ms
             // $foo.testBool = 0;
             // $foo.testString = "HUHU";
             // %int = $foo.testInt;
             // $foo.testSlot[1] ++;
        }
    }
    else
    // 145 ms
    if ($mode == 9) {
        %foo = $foo;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
            %x = %foo.x + %i;
            %y = %foo.y + %i;
            %foo.setPoint(%i, %x, %y);
        }
    }
    else
    // 109 ms
    if ($mode == 10) {
        %foo = $foo;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
            // this push the Vector2F to .x, .y
            %foo.pushPoint(%i);
            // with type casting it's faster!!
            %x = %foo.x * 1;
            %y = %foo.y * 1;
        }
    }
    // 150ms
    if ($mode == 11) {
         %foo = $foo;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {

            %p = %foo.getPoint(%i);
            //here it is the same with type casting
            %x = %p.x * 1;
            %y = %p.y * 1;
        }
    }
    // 110 ms ** same as 10 but with Engine function ! << exaxt same speed
    if ($mode == 12) {
        %foo = $foo;
        for (%i =0 ; %i < LOOP_COUNT; %i++) {
            // this push the Vector2F to .x, .y
            Test_PushPoint(%foo, %i);
            %x = %foo.x * 1;
            %y = %foo.y * 1;
        }
    }
}


$i = 0; $times = 0;
// called from c++ mainloop
function MainLoop() {

    if ($mode >= 0) {
        $i++;
        $times += GetFrameTime();
        if ($i >= 10) {
            $i -= 10;
            echo("Speedtest MODE:" SPC $mode SPC "avg time:" SPC $times / 10 SPC "testfloat/int/bool:" SPC $foo.testFloat SPC $foo.testInt SPC $foo.testBool);
            $times = 0;
        }
    }
    SpeedTest();

}
