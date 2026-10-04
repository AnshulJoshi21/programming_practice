// 1BIT NAND
module nand_gate(
  input logic a,
  input logic b,
  output logic y
);

  assign y = ~(a & b);

endmodule

module not_gate #(
  parameter int WIDTH = 1
) (
  input logic [WIDTH-1:0] a,
  output logic [WIDTH-1:0] y
);

  genvar i;

  generate
    for (i = 0; i < WIDTH; i++) begin : gen_not

      nand_gate nand1(
        .a(a[i]),
        .b(a[i]),
        .y(y[i])
      );
    
    end
  endgenerate

endmodule

module and_gate #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  output logic [WIDTH-1:0] y
);

  genvar i;
  logic [WIDTH-1:0] nand_out;

  generate
    for (i = 0; i < WIDTH; i++) begin : gen_and

      nand_gate nand1(
        .a(a[i]),
        .b(b[i]),
        .y(nand_out[i])
      );

      not_gate not1(
        .a(nand_out[i]),
        .y(y[i])
      );
      
    end
  endgenerate

endmodule

module or_gate #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  output logic [WIDTH-1:0] y
);

  genvar i;

  logic [WIDTH-1:0] not_a;
  not_gate #(.WIDTH(WIDTH)) not1(.a(a), .y(not_a)) ;

  logic [WIDTH-1:0] not_b;
  not_gate #(.WIDTH(WIDTH)) not2(.a(b), .y(not_b)) ;

  generate
    for (i = 0; i < WIDTH; i++) begin: gen_or
      nand_gate nand1(
        .a(not_a[i]),
        .b(not_b[i]),
        .y(y[i])
      );
    end
  endgenerate

endmodule

module nor_gate #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  output logic [WIDTH-1:0] y
);

  logic [WIDTH-1:0] or_out;
  or_gate #(.WIDTH(WIDTH)) or1(
    .a(a),
    .b(b),
    .y(or_out)
  );

  not_gate #(.WIDTH(WIDTH)) not1(
    .a(or_out),
    .y(y)
  );

endmodule

module xor_gate #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  output logic [WIDTH-1:0] y
);

  logic [WIDTH-1:0] not_a;
  logic [WIDTH-1:0] not_b;

  not_gate #(.WIDTH(WIDTH)) not1(
    .a(a),
    .y(not_a)
  );

  not_gate #(.WIDTH(WIDTH)) not2(
    .a(b),
    .y(not_b)
  );
  
  logic [WIDTH-1:0] and1_out;
  logic [WIDTH-1:0] and2_out;

  and_gate #(.WIDTH(WIDTH)) and1(
    .a(not_a),
    .b(b),
    .y(and1_out)
  );

  and_gate #(.WIDTH(WIDTH)) and2(
    .a(a),
    .b(not_b),
    .y(and2_out)
  );

  or_gate #(.WIDTH(WIDTH)) or1(
    .a(and1_out),
    .b(and2_out),
    .y(y)
  );

endmodule

module xnor_gate #(
  parameter int WIDTH = 1
)(
  input logic [WIDTH-1:0] a,
  input logic [WIDTH-1:0] b,
  output logic [WIDTH-1:0] y
);

  logic [WIDTH-1:0] xor_out;
  
  xor_gate #(.WIDTH(WIDTH)) xor1(
    .a(a),
    .b(b),
    .y(xor_out)
  );

  not_gate #(.WIDTH(WIDTH)) not1(
    .a(xor_out),
    .y(y)
  );

endmodule
