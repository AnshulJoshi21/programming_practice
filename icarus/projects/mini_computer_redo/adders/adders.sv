module half_adder(
  input logic a,
  input logic b,
  output logic sum,
  output logic cout
);

  xor_gate #(.WIDTH(1)) xor1(
    .a(a),
    .b(b),
    .y(sum)
  );

  and_gate #(.WIDTH(1)) and1(
    .a(a),
    .b(b),
    .y(cout)
  );

endmodule

module full_adder #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  input logic cin,
  output logic [WIDTH-1:0] sum,
  output logic cout
);

  logic [WIDTH-1:0] ha1_sum;

  logic [WIDTH:0] ha1_cout;
  assign ha1_cout[0] = cin;

  logic [WIDTH:0] ha2_cout;
  assign ha2_cout[0] = 1'b0;

  genvar i;

  generate
    for (i = 0; i < WIDTH; i++) begin : ha_gen
      half_adder ha1(
        .a(a[i]),
        .b(b[i]),
        .sum(ha1_sum[i]),
        .cout(ha1_cout[i + 1])
      );

      half_adder ha2(
        .a(ha1_sum[i]),
        .b(ha1_cout[i]),
        .sum(sum[i]),
        .cout(ha2_cout[i + 1])
      );
    end
  endgenerate

  or_gate #(.WIDTH(1)) or1(
    .a(ha1_cout[WIDTH]),
    .b(ha2_cout[WIDTH]),
    .y(cout)
  );

endmodule
