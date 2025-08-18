module half_adder_tb;
 
  reg in1 = 0;
  reg in2 = 0;
  wire out;
  wire car;

  half_adder ha (
    .input1(in1),
    .input2(in2),
    .sum (out),
    .carry(car)
  );


  initial begin
    $dumpfile("wave.vcd");       //產生vcd name
    $dumpvars(0, half_adder_tb);    //tb module name
    in1 = 1'b0;
    in2 = 1'b0;
    #2
    in1 = 1'b1;
    in2 = 1'b0;
    #2
    in1 = 1'b0;
    in2 = 1'b1;
    #2
    in1 = 1'b1;
    in2 = 1'b1;
  end
 
endmodule