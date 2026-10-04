module mux_2x1(
    input wire sel,
    input wire [1:0] data,
    output wire y
);

    wire not_sel;
    not_gate not1(
        .a(sel), 
        .y(not_sel)
    );

    wire and_out1;
    wire and_out2;

    and_gate and1(
        .a(not_sel),
        .b(data[0]),
        .y(and_out1)
    );

    and_gate and2(
        .a(sel),
        .b(data[1]),
        .y(and_out2)
    );

    or_gate or1(
        .a(and_out1),
        .b(and_out2),
        .y(y)
    );

endmodule

module mux_4x1(
    input wire [1:0] sel,
    input wire [3:0] data,
    output wire y
);

    wire m1_out;
    wire m2_out;

    mux_2x1 m1(
        .sel(sel[0]),
        .data(data[1:0]),
        .y(m1_out)
    );

    mux_2x1 m2(
        .sel(sel[0]),
        .data(data[3:2]),
        .y(m2_out)
    );

    mux_2x1 m3(
        .sel(sel[1]),
        .data({m2_out, m1_out}),
        .y(y)
    );

endmodule

module mux_8x1(
    input wire [2:0] sel,
    input wire [7:0] data,
    output wire y
);

    wire m1_out;
    wire m2_out;

    mux_4x1 m1(
        .sel(sel[1:0]),
        .data(data[3:0]),
        .y(m1_out)
    );

    mux_4x1 m2(
        .sel(sel[1:0]),
        .data(data[7:4]),
        .y(m2_out)
    );

    mux_2x1 m3(
        .sel(sel[2]),
        .data({m2_out, m1_out}),
        .y(y)
    );

endmodule