`timescale 1ns/100ps
module practice_1 (
    input wire A,
    input wire B,
    input wire C,
    output wire out
);

    wire O1, O2;
    and (O1, A, B);
    or (O2, A, B);
    mux m1 (
        .a(O1),
        .b(O2),
        .c(C),
        .y(out)
    );

endmodule

module mux (
    input wire a,
    input wire b,
    input wire c,
    output wire y
);

    wire not_c;
    wire o1, o2;
    not (not_c, c);
    and (o1, a, not_c);
    and (o2, b, c);
    or (y, o1, o2);

endmodule