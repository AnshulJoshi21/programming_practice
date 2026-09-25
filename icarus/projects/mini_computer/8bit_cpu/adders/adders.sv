// HALF ADDER
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

// FULL ADDER
module full_adder(
  input wire a,
  input wire b,
  input wire cin,

  output wire sum,
  output wire carry
);

  wire h1_sum;
  wire h1_carry;
  wire h2_carry;

  half_adder h1(
    .a(a),
    .b(b),
    .sum(h1_sum),
    .carry(h1_carry)
  );

  half_adder h2(
    .a(h1_sum),
    .b(cin),
    .sum(sum),
    .carry(h2_carry)
  );

  or_gate or1(
    .a(h1_carry),
    .b(h2_carry),
    .y(carry)
  );

endmodule

