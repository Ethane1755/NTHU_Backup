`timescale 1ns/100ps

module practice_2(
  input wire G,
  input wire D,
  output wire P,
  output wire Pn
);
  wire Dn, S, R, Qn, Q;

  not (Dn, D);         
  and (S, D, G);      
  and (R, Dn, G);     
  nor (Q, R, Qn);
  nor (Qn, S, Q);  

  assign Pn = Qn; 
  assign P = Q;

endmodule
