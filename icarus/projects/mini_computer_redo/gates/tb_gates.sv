module tb_gates;

  parameter int WIDTH = 1;

  logic a1;
  logic b1;

  logic nand_y;

  logic [WIDTH-1:0] a;
  logic [WIDTH-1:0] b;

  logic [WIDTH-1:0] not_y;
  logic [WIDTH-1:0] and_y;
  logic [WIDTH-1:0] or_y;
  logic [WIDTH-1:0] nor_y;
  logic [WIDTH-1:0] xor_y;
  logic [WIDTH-1:0] xnor_y;

  nand_gate nand1(
    .a(a1),
    .b(b1),
    .y(nand_y)
  );

  not_gate #(.WIDTH(WIDTH)) not1(
    .a(a),
    .y(not_y)
  );

  and_gate #(.WIDTH(WIDTH)) and1(
    .a(a),
    .b(b),
    .y(and_y)
  );

  or_gate #(.WIDTH(WIDTH)) or1(
    .a(a),
    .b(b),
    .y(or_y)
  );

  nor_gate #(.WIDTH(WIDTH)) nor1(
    .a(a),
    .b(b),
    .y(nor_y)
  );

  xor_gate #(.WIDTH(WIDTH)) xor1(
    .a(a),
    .b(b),
    .y(xor_y)
  );

  xnor_gate #(.WIDTH(WIDTH)) xnor1(
    .a(a),
    .b(b),
    .y(xnor_y)
  );

  initial begin
    $dumpfile("gates_waveform.vcd");
    $dumpvars(0, tb_gates);

    a1=1'b0; b1=1'b0; a=1'b0; b=1'b0; #10;
    a1=1'b0; b1=1'b1; a=1'b0; b=1'b1; #10;
    a1=1'b1; b1=1'b0; a=1'b1; b=1'b0; #10;
    a1=1'b1; b1=1'b1; a=1'b1; b=1'b1; #10;
  
    $finish;
  end

endmodule

