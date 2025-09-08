`timescale 1ns/100ps

module practice_2(
  input wire G,
  input wire D,
  output wire P,
  output wire Pn
);
  wire Dn, S, R, Qn, Q;
  wire Sn, Rn;

  not (Dn, D);         
  nand (S, D, G);
  nand (R, Dn, G);
  nand (Q, S, Qn);
  nand (Qn, R, Q);
  
  assign P = Q;
  assign Pn = Qn;

endmodule
