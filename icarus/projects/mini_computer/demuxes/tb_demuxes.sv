module tb_demuxes;

    reg [2:0] sel;
    reg data;

    wire [1:0] y2;
    wire [3:0] y4;
    wire [7:0] y8;

    dmux_1x2 dm1(
        .sel(sel[0]),
        .data(data),
        .y(y2)
    );

    dmux_1x4 dm2(
        .sel(sel[1:0]),
        .data(data),
        .y(y4)
    );

    dmux_1x8 dm3(
        .sel(sel),
        .data(data),
        .y(y8)
    );

    initial begin
        $dumpfile("demuxes_wf.vcd");
        $dumpvars(0, tb_demuxes);

        data=0;

        sel=3'b000; #10;
        sel=3'b001; #10;
        sel=3'b010; #10;
        sel=3'b011; #10;
        sel=3'b100; #10;
        sel=3'b101; #10;
        sel=3'b110; #10;
        sel=3'b111; #10;

        data=1;

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