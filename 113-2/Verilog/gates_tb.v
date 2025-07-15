module tb;
    reg a;
    reg b;
    wire o;
    wire o1;

    not_gate uut(.a(a), .o(o));
    and_gate uut1 (.a(a), .b(b), .o1(o1));

    initial begin
        $monitor("Time: %0t, a = %b, b = %b, o = %b, o1 = %b", $time, a, b, o, o1);
        a = 0; b = 0;
        #10
        a = 1; b = 0;
        #10
        a = 0; b = 1;
        #10
        a = 1; b = 1;
        #10
        $finish();
    end

    initial
    begin
        $dumpfile("tb.vcd");
        $dumpvars(0, tb);
    end

endmodule




