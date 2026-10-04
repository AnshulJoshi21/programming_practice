module not8(
    input wire [7:0] a,
    output wire [7:0] y
);
    genvar i;

    generate
        for (i = 0; i < 8; i = i + 1) begin
            not_gate not1(
                .a(a[i]),
                .y(y[i])
            );
        end
    endgenerate

endmodule

module and8(
    input wire [7:0] a,
    input wire [7:0] b,
    output wire [7:0] y
);

    genvar i;

    generate
        for (i = 0; i < 8; i = i + 1) begin
            and_gate and1(
                .a(a[i]),
                .b(b[i]),
                .y(y[i])
            );
        end
    endgenerate

endmodule

module or8(
    input wire [7:0] a,
    input wire [7:0] b,
    output wire [7:0] y
);

    genvar i;

    generate
        for (i = 0; i < 8; i = i + 1) begin
            or_gate or1(
                .a(a[i]),
                .b(b[i]),
                .y(y[i])
            );
        end
    endgenerate

endmodule

module xor8(
    input wire [7:0] a,
    input wire [7:0] b,
    output wire [7:0] y
);

    genvar i;

    generate
        for (i = 0; i < 8; i = i + 1) begin
            xor_gate xor1(
                .a(a[i]),
                .b(b[i]),
                .y(y[i])
            );
        end
    endgenerate

endmodule

module add8(
    input wire [7:0] a,
    input wire [7:0] b,
    output wire [7:0] sum,
    output wire carry
);

    genvar i;
    wire [8:0] temp_carry;
    assign temp_carry[0] = 1'b0;

    generate
        for (i = 0; i < 8; i = i + 1) begin
            full_adder fa(
                .a(a[i]),
                .b(b[i]),
                .cin(temp_carry[i]),
                .sum(sum[i]),
                .carry(temp_carry[i + 1])
            );
        end
    endgenerate

    assign carry = temp_carry[8];

endmodule

module sub8(
    input wire [7:0] a,
    input wire [7:0] b,
    output wire [7:0] sum,
    output wire carry
);

    genvar i;

    wire [8:0] temp_carry;
    assign temp_carry[0] = 1'b1;

    wire [7:0] not_out;

    generate
        for (i = 0; i < 8; i = i + 1) begin
            not_gate not1(
                .a(b[i]),
                .y(not_out[i])
            );

            full_adder fa(
                .a(a[i]),
                .b(not_out[i]),
                .cin(temp_carry[i]),
                .sum(sum[i]),
                .carry(temp_carry[i + 1])
            );
        end
    endgenerate

    assign carry = temp_carry[8];

endmodule

module shl8(
    input wire [7:0] a,
    output wire [7:0] y
);
    genvar i;

    generate
        for (i = 1; i < 8; i = i + 1) begin 
            assign y[i] = a[i - 1];
        end
    endgenerate

    assign y[0] = 0;

endmodule

module shr8(
    input wire [7:0] a,
    output wire [7:0] y
);

    genvar i;

    generate 
        for (i = 0; i < 7; i = i + 1) begin
            assign y[i] = a[i + 1];
        end
    endgenerate

    assign y[7] = 0;

endmodule