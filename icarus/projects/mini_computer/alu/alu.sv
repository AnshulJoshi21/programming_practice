/*
opcode:
  000 ADD
  001 SUB
  010 AND
  011 OR
  100 XOR
  101 NOT - a
  110 SHL (logical) - a
  111 SHR (logical) - a
*/
module alu(
  input wire [2:0] opcode,
  input wire [7:0] a,
  input wire [7:0] b,

  output wire [7:0] result,
  output wire carry,
  output wire zero,
  output wire sign,
  output wire overflow  
);

  // basic operations
  wire [7:0] add8_sum;
  wire       add8_carry;
  wire [7:0] sub8_sum;
  wire       sub8_carry;
  wire [7:0] and8_result;
  wire [7:0] or8_result;
  wire [7:0] xor8_result;
  wire [7:0] not8_result;
  wire [7:0] shl8_result;
  wire [7:0] shr8_result;

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

  and8 and8(
    .a(a),
    .b(b),
    .y(and8_result)
  );

  or8 or8(
    .a(a),
    .b(b),
    .y(or8_result)
  );

  xor8 xor8(
    .a(a),
    .b(b),
    .y(xor8_result)
  );

  not8 not8(
    .a(a),
    .y(not8_result)
  );

  shl8 shl8(
    .a(a),
    .y(shl8_result)
  );

  shr8 shr8(
    .a(a),
    .y(shr8_result)
  );

  genvar i;

  generate
    for (i = 0; i < 8; i = i + 1) begin
      mux_8x1 mux1(
        .sel(opcode),
        .data({
          add8_sum[i],
          sub8_sum[i],
          and8_result[i],
          or8_result[i],
          xor8_result[i],
          not8_result[i],
          shl8_result[i],
          shr8_result[i]
         }),
        .y(result[i])
      );
    end
  endgenerate

  // carry
  mux_8x1 mux2(
    .sel(opcode),
    .data({add8_carry, sub8_carry, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0}), // 0 for non carry operations
    .y(carry)
  );

  // zero
  wire [7:0] not8_new_result;
  not8 not8_1(
    .a(result),
    .y(not8_new_result)
  );

  wire [8:0] temp_zero;
  assign temp_zero[0] = 1'b1;

  generate
    for (i = 0; i < 8; i = i + 1) begin
      and_gate and1(
        .a(temp_zero[i]),
        .b(not8_new_result[i]),
        .y(temp_zero[i + 1])
      );
    end
  endgenerate

  assign zero = temp_zero[8];


  // SIGN
  assign sign = result[7];

  // OVERFLOW
  // 
  wire overflow_add;
  wire xnor_add1;  
  wire xor_add1;  

  // addition overflow
  xnor_gate xnor1(
    .a(a[7]),
    .b(b[7]),
    .y(xnor_add1)
  );

  xor_gate xor1(
    .a(a[7]),
    .b(result[7]),
    .y(xor_add1)
  );

  and_gate and1(
    .a(xnor_add1),
    .b(xor_add1),
    .y(overflow_add)
  );

  // sub overflow
  wire overflow_sub;
  wire xor_sub1;  
  wire xor_sub2;  

  xor_gate xor2(
    .a(a[7]),
    .b(b[7]),
    .y(xor_sub1)
  );

  xor_gate xor3(
    .a(a[7]),
    .b(result[7]),
    .y(xor_sub2)
  );

  and_gate and2(
    .a(xor_sub1),
    .b(xor_sub2),
    .y(overflow_sub)
  );

  wire is_arith;
  wire not_op1;
  wire not_op2;

  not_gate not1(
    .a(opcode[1]),
    .y(not_op1)
  );

  not_gate not2(
    .a(opcode[2]),
    .y(not_op2)
  );

  and_gate and3(
    .a(not_op2),
    .b(not_op1),
    .y(is_arith)
  );

  // final overflow
  wire overflow_selected;
  mux_2x1 mux3(
    .sel(opcode[0]),
    .data({overflow_sub, overflow_add}),
    .y(overflow_selected)
  );

  and_gate and4(
    .a(overflow_selected),
    .b(is_arith),
    .y(overflow)
  );

endmodule
