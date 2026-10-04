module tb_operations;

    reg [7:0] a;
    reg [7:0] b;
    
    wire [7:0] not8_y;
    wire [7:0] and8_y;
    wire [7:0] or8_y;
    wire [7:0] xor8_y;

    wire [7:0] add8_sum;
    wire add8_carry;
    wire [7:0] sub8_sum;
    wire sub8_carry;

    wire [7:0] shl8_y;
    wire [7:0] shr8_y;

    not8 not8(
        .a(a),
        .y(not8_y)
    );

    and8 and8(
        .a(a),
        .b(b),
        .y(and8_y)
    );

    or8 or8(
        .a(a),
        .b(b),
        .y(or8_y)
    );

    xor8 xor8(
        .a(a),
        .b(b),
        .y(xor8_y)
    );

    add8 add8(
        .a(a),
        .b(b),
        .sum(add8_sum),
        .carry(add8_carry)
    );

    sub8 sub8(
        .a(a),
        .b(b),
        .sum(sub8_sum),
        .carry(sub8_carry)
    );

    shl8 shl8(
        .a(a),
        .y(shl8_y)
    );

    shr8 shr8(
        .a(a),
        .y(shr8_y)
    );

    initial begin
        $dumpfile("operations_wf.vcd");
        $dumpvars(0, tb_operations);

        a = 8'b00000101;
        b = 8'b00000011;
        #10;

        a = 8'b11111111;
        b = 8'b00000001;
        #10;

        a = 8'b10101010;
        b = 8'b01010101;
        #10;

        a = 8'b00000000;
        b = 8'b00000000;
        #10;

        $finish;
    end

endmodule
