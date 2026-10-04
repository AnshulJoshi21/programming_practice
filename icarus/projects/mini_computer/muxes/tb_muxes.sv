module tb_muxes;

    reg [2:0] sel;
    reg [7:0] data;

    wire y2;
    wire y4;
    wire y8;

    mux_2x1 m1(
        .sel(sel[0]),
        .data(data[1:0]),
        .y(y2)
    );

    mux_4x1 m2(
        .sel(sel[1:0]),
        .data(data[3:0]),
        .y(y4)
    );

    mux_8x1 m3(
        .sel(sel),
        .data(data),
        .y(y8)
    );

    initial begin
        $dumpfile("muxes_wf.vcd");
        $dumpvars(0, tb_muxes);

        data=8'b10110101;

        sel=3'b000; #10;
        sel=3'b001; #10;
        sel=3'b010; #10;
        sel=3'b011; #10;
        sel=3'b100; #10;
        sel=3'b101; #10;
        sel=3'b110; #10;
        sel=3'b111; #10;

        $finish;
    end

endmodule