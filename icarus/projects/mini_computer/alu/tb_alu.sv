module tb_alu;

  reg [2:0] opcode;
  reg [7:0] a;
  reg [7:0] b;

  wire [7:0] result;
  wire carry;
  wire zero;
  wire sign;
  wire overflow;

  alu dut(
   .opcode(opcode),
   .a(a),
   .b(b),

   .result(result),
   .carry(carry),
   .zero(zero),
   .sign(sign),
   .overflow(overflow)
  );

  initial begin
    $dumpfile("alu_wf.vcd");
    $dumpvars(0, tb_alu);

    // Test 1
    opcode = 3'b000;
    a = 8'h05;
    b = 8'h03;
    #10;

    // Test 2
    opcode = 3'b001;
    a = 8'h08;
    b = 8'h03;
    #10;

    // Test 3
    opcode = 3'b010;
    a = 8'hFF;
    b = 8'h01;
    #10;

    // Test 4
    opcode = 3'b011;
    a = 8'h0F;
    b = 8'hF0;
    #10;

    // Test 5
    opcode = 3'b100;
    a = 8'h0F;
    b = 8'hF0;
    #10;

    // Test 6: zero result
    opcode = 3'b001;
    a = 8'h05;
    b = 8'h05;
    #10;

    // Test 7: negative/sign result
    opcode = 3'b000;
    a = 8'h80;
    b = 8'h01;
    #10;

    // Test 8: signed overflow example
    opcode = 3'b000;
    a = 8'h7F;
    b = 8'h01;
    #10;
     
    $finish;
  end

endmodule
