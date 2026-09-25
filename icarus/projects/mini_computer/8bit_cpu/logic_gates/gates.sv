// NAND GATE
module nand_gate(
  input wire a,
  input wire b,
  output wire y
);

  assign y = ~(a & b);

endmodule

// NOT GATE
module not_gate(
  input wire a,
  output wire y
);

  nand_gate nand1(
    .a(a),
    .b(a),
    .y(y)
  );

endmodule

// AND GATE
module and_gate(
  input wire a,
  input wire b,
  output wire y
);

  wire nand_out;

  nand_gate nand1(
    .a(a),
    .b(b),
    .y(nand_out)
  );

  not_gate not1(
    .a(nand_out),
    .y(y)
  );

endmodule

// OR GATE
module or_gate(
  input wire a,  
  input wire b,  
  output wire y 
);

  wire not_out1;
  wire not_out2;

  not_gate not1(
    .a(a),    
    .y(not_out1)
  );

  not_gate not2(
    .a(b),    
    .y(not_out2)
  );

  nand_gate nand1(
    .a(not_out1),
    .b(not_out2),
    .y(y)
  );

endmodule

// NOR GATE
module nor_gate(
  input wire a,
  input wire b,
  output wire y
);

  wire or_out;

  or_gate or1(
    .a(a),
    .b(b),
    .y(or_out)
  );

  
  not_gate not1(
    .a(or_out),
    .y(y)
  );

endmodule

// XOR GATE
module xor_gate(
  input wire a,
  input wire b,
  output wire y
);

  wire not_a;
  wire not_b;

  not_gate not1(
    .a(a),
    .y(not_a)
  );

  not_gate not2(
    .a(b),
    .y(not_b)
  );

  wire and_out1;
  wire and_out2;

  and_gate and1(
    .a(not_a),  
    .b(b),
    .y(and_out1)
  );

  and_gate and2(
    .a(a),  
    .b(not_b),
    .y(and_out2)
  );

  or_gate or1(
    .a(and_out1),
    .b(and_out2),
    .y(y)
  );

endmodule

// XNOR GATE
module xnor_gate(
  input wire a,
  input wire b,
  output wire y
);

  wire xor_out;

  xor_gate xor1(
    .a(a),
    .b(b),
    .y(xor_out)
  );

  not_gate not1(
    .a(xor_out),
    .y(y)
  );

endmodule

