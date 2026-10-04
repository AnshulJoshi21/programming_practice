module tb_gates;

    reg a;
    reg b;
    
    wire nand_y;
    wire not_y;
    wire and_y;
    wire or_y;
    wire nor_y;
    wire xor_y;
    wire xnor_y;

    nand_gate nand1(
        .a(a),
        .b(b),
        .y(nand_y)
    );

    not_gate not1(
        .a(a),
        .y(not_y)
    );

    and_gate and1(
        .a(a),
        .b(b),
        .y(and_y)
    );

    or_gate or1(
        .a(a),
        .b(b),
        .y(or_y)
    );

    nor_gate nor1(
        .a(a),
        .b(b),
        .y(nor_y)
    );

    xor_gate xor1(
        .a(a),
        .b(b),
        .y(xor_y)
    );

    xnor_gate xnor1(
        .a(a),
        .b(b),
        .y(xnor_y)
    );

    initial begin
        $dumpfile("gates_wf.vcd");
        $dumpvars(0, tb_gates);

        a=0; b=0; #10;
        a=0; b=1; #10;
        a=1; b=0; #10;
        a=1; b=1; #10;

        $finish;
    end

endmodule