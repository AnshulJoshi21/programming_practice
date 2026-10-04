module half_adder(
  input wire a,
  input wire b,
  output wire sum,
  output wire carry
);

  xor_gate xor1(
    .a(a),
    .b(b),
    .y(sum)
  );

  and_gate and1(
    .a(a),
    .b(b),
    .y(carry)
  );

endmodule

module full_adder(
  input wire a,
  input wire b,
  input wire cin,
  output wire sum,
  output wire carry
);

  wire ha1_sum;
  wire ha1_carry;
  wire ha2_carry;

  half_adder ha1(
    .a(a),
    .b(b),
    .sum(ha1_sum),
    .carry(ha1_carry)
  );

  half_adder ha2(
    .a(ha1_sum),
    .b(cin),
    .sum(sum),
    .carry(ha2_carry)
  );

  or_gate or1(
    .a(ha1_carry),
    .b(ha2_carry),
    .y(carry)
  );

endmodule
