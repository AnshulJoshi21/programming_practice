module dmux_1x2(
    input wire sel,
    input wire data,
    output wire [1:0] y
);

    wire not_sel;
    not_gate not1(
        .a(sel),
        .y(not_sel)
    );

    and_gate and1(
        .a(not_sel),
        .b(data),
        .y(y[0])
    );

    and_gate and2(
        .a(sel),
        .b(data),
        .y(y[1])
    );

endmodule

module dmux_1x4(
    input wire [1:0] sel,
    input wire data,
    output wire [3:0] y
);

    wire [1:0] dm1_out;
    dmux_1x2 dm1(
        .sel(sel[1]),
        .data(data),
        .y(dm1_out)
    );

    dmux_1x2 dm2(
        .sel(sel[0]),
        .data(dm1_out[0]),
        .y(y[1:0])
    );

    dmux_1x2 dm3(
        .sel(sel[0]),
        .data(dm1_out[1]),
        .y(y[3:2])
    );

endmodule

module dmux_1x8(
    input wire [2:0] sel,
    input wire data,
    output wire [7:0] y
);

    wire [1:0] dm1_out;
    dmux_1x2 dm1(
        .sel(sel[2]),
        .data(data),
        .y(dm1_out)
    );

    dmux_1x4 dm2(
        .sel(sel[1:0]),
        .data(dm1_out[0]),
        .y(y[3:0])
    );

    dmux_1x4 dm3(
        .sel(sel[1:0]),
        .data(dm1_out[1]),
        .y(y[7:4])
    );

endmodule