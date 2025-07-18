module DFF_tb;

// Testbench signals
reg D;
reg clk;
wire Q;

// Instantiate the D flip-flop
DFF dut (
    .D(D),
    .clk(clk),
    .Q(Q)
);

// Clock generation
initial begin
    clk = 0;
    forever #5 clk = ~clk; // 10ns period clock (100MHz)
end

// Test stimulus
initial begin
    // Initialize signals
    D = 0;
    
    // Wait for a few clock cycles
    #10;
    
    // Test case 1: D = 0, should see Q = 0 after clock edge
    D = 0;
    #10;
    $display("Time: %0t, D = %b, Q = %b", $time, D, Q);
    
    // Test case 2: D = 1, should see Q = 1 after clock edge
    D = 1;
    #10;
    $display("Time: %0t, D = %b, Q = %b", $time, D, Q);
    
    // Test case 3: D = 0, should see Q = 0 after clock edge
    D = 0;
    #10;
    $display("Time: %0t, D = %b, Q = %b", $time, D, Q);
    
    // Test case 4: D = 1, should see Q = 1 after clock edge
    D = 1;
    #10;
    $display("Time: %0t, D = %b, Q = %b", $time, D, Q);
    
    // Test rapid changes within a clock cycle
    D = 0;
    #2;
    D = 1;
    #3;
    D = 0;
    #5; // Wait for clock edge
    $display("Time: %0t, D = %b, Q = %b (should be 0 - last value before clock)", $time, D, Q);
    
    // Test holding D high for multiple cycles
    D = 1;
    #20;
    $display("Time: %0t, D = %b, Q = %b", $time, D, Q);
    
    // Final test
    D = 0;
    #10;
    $display("Time: %0t, D = %b, Q = %b", $time, D, Q);
    
    // End simulation
    #20;
    $display("Testbench completed successfully!");
    $finish;
end

// Monitor changes
initial begin
    $monitor("Time: %0t | clk: %b | D: %b | Q: %b", $time, clk, D, Q);
end

// Generate VCD file for waveform viewing
initial begin
    $dumpfile("DFF_tb.vcd");
    $dumpvars(0, DFF_tb);
end

endmodule
