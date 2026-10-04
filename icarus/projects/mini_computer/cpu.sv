// LOGIC GATES
module nand_gate(
  input wire a,
  input wire b,
  output wire y
);

  assign y = ~(a & b);
  
endmodule

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

module or_gate(
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

  nand_gate nand1(
    .a(not_a),
    .b(not_b),
    .y(y)
  );

endmodule

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

// LOGIC GATES TESTS
module tb_gates;

  reg a;
  reg b;
  wire nand_y;
  wire not_y;
  wire and_y;
  wire or_y;
  wire nor_y;
  wire xor_y;
  wire xnor_y;

  nand_gate nand1(
    .a(a),
    .b(b),
    .y(nand_y)
  );

  not_gate not1(
    .a(a),
    .y(not_y)
  );

  and_gate and1(
    .a(a),
    .b(b),
    .y(and_y)
  );

  or_gate or1(
    .a(a),
    .b(b),
    .y(or_y)
  );

  nor_gate nor1(
    .a(a),
    .b(b),
    .y(nor_y)
  );

  xor_gate xor1(
    .a(a),
    .b(b),
    .y(xor_y)
  );

  xnor_gate xnor1(
    .a(a),
    .b(b),
    .y(xnor_y)
  );

  initial begin
    a=0; b=0; #10;
    if (nand_y !== 1'b1) $display("ERROR: NAND(0, 0) = %b", nand_y);
    if (not_y  !== 1'b1) $display("ERROR: NOT(0) = %b", not_y);
    if (and_y  !== 1'b0) $display("ERROR: AND(0, 0) = %b", and_y);
    if (or_y   !== 1'b0) $display("ERROR: OR(0, 0) = %b", or_y);
    if (nor_y  !== 1'b1) $display("ERROR: NOR(0, 0) = %b", nor_y);
    if (xor_y  !== 1'b0) $display("ERROR: XOR(0, 0) = %b", xor_y);
    if (xnor_y !== 1'b1) $display("ERROR: XNOR(0, 0) = %b", xnor_y);
    
    a=0; b=1; #10;
    if (nand_y !== 1'b1) $display("ERROR: NAND(0, 1) = %b", nand_y);
    if (not_y  !== 1'b1) $display("ERROR: NOT(0) = %b", not_y);
    if (and_y  !== 1'b0) $display("ERROR: AND(0, 1) = %b", and_y);
    if (or_y   !== 1'b1) $display("ERROR: OR(0, 1) = %b", or_y);
    if (nor_y  !== 1'b0) $display("ERROR: NOR(0, 1) = %b", nor_y);
    if (xor_y  !== 1'b1) $display("ERROR: XOR(0, 1) = %b", xor_y);
    if (xnor_y !== 1'b0) $display("ERROR: XNOR(0, 1) = %b", xnor_y);
    
    a=1; b=0; #10;
    if (nand_y !== 1'b1) $display("ERROR: NAND(1, 0) = %b", nand_y);
    if (not_y  !== 1'b0) $display("ERROR: NOT(1) = %b", not_y);
    if (and_y  !== 1'b0) $display("ERROR: AND(1, 0) = %b", and_y);
    if (or_y   !== 1'b1) $display("ERROR: OR(1, 0) = %b", or_y);
    if (nor_y  !== 1'b0) $display("ERROR: NOR(1, 0) = %b", nor_y);
    if (xor_y  !== 1'b1) $display("ERROR: XOR(1, 0) = %b", xor_y);
    if (xnor_y !== 1'b0) $display("ERROR: XNOR(1, 0) = %b", xnor_y);
    
    a=1; b=1; #10;
    if (nand_y !== 1'b0) $display("ERROR: NAND(1, 1) = %b", nand_y);
    if (not_y  !== 1'b0) $display("ERROR: NOT(1) = %b", not_y);
    if (and_y  !== 1'b1) $display("ERROR: AND(1, 1) = %b", and_y);
    if (or_y   !== 1'b1) $display("ERROR: OR(1, 1) = %b", or_y);
    if (nor_y  !== 1'b0) $display("ERROR: NOR(1, 1) = %b", nor_y);
    if (xor_y  !== 1'b0) $display("ERROR: XOR(1, 1) = %b", xor_y);
    if (xnor_y !== 1'b1) $display("ERROR: XNOR(1, 1) = %b", xnor_y);
    
    $display("All gate tests passed");
  end

endmodule


// ADDERS
module half_adder(
  input wire a,
  input wire b,
  output wire y,
  output wire carry
);

  xor_gate xor1(
    .a(a),
    .b(b),
    .y(y)
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
  output wire y,
  output wire carry
);

  wire ha1_y;
  wire ha1_carry;
  wire ha2_carry;

  half_adder ha1(
    .a(a),
    .b(b),
    .y(ha1_y),
    .carry(ha1_carry)
  );

  half_adder ha2(
    .a(ha1_y),
    .b(cin),
    .y(y),
    .carry(ha2_carry)
  );

  or_gate or1(
    .a(ha1_carry),
    .b(ha2_carry),
    .y(carry)
  );

endmodule

// ADDERS TESTS
module tb_adders;

  reg a;
  reg b;
  reg cin;
  wire ha_y;
  wire ha_carry;
  wire fa_y;
  wire fa_carry;

  half_adder ha(
    .a(a),
    .b(b),
    .y(ha_y),
    .carry(ha_carry)
  );

  full_adder fa(
    .a(a),
    .b(b),
    .cin(cin),
    .y(fa_y),
    .carry(fa_carry)
  );

  initial begin
    a=0; b=0; cin=0; #10;
    if (ha_y !== 1'b0 || ha_carry !== 1'b0) $display("ERROR: HALF_ADDER(0, 0) = %b, %b", ha_y, ha_carry);
    if (fa_y !== 1'b0 || fa_carry !== 1'b0) $display("ERROR: fULL_ADDER(0, 0, 0) = %b, %b", fa_y, fa_carry);
    
    a=0; b=0; cin=1; #10;
    if (ha_y !== 1'b0 || ha_carry !== 1'b0) $display("ERROR: HALF_ADDER(0, 0) = %b, %b", ha_y, ha_carry);
    if (fa_y !== 1'b1 || fa_carry !== 1'b0) $display("ERROR: fULL_ADDER(0, 0, 1) = %b, %b", fa_y, fa_carry);
    
    a=0; b=1; cin=0; #10;
    if (ha_y !== 1'b1 || ha_carry !== 1'b0) $display("ERROR: HALF_ADDER(0, 1) = %b, %b", ha_y, ha_carry);
    if (fa_y !== 1'b1 || fa_carry !== 1'b0) $display("ERROR: fULL_ADDER(0, 1, 0) = %b, %b", fa_y, fa_carry);
    
    a=0; b=1; cin=1; #10;
    if (ha_y !== 1'b1 || ha_carry !== 1'b0) $display("ERROR: HALF_ADDER(0, 1) = %b, %b", ha_y, ha_carry);
    if (fa_y !== 1'b0 || fa_carry !== 1'b1) $display("ERROR: fULL_ADDER(0, 1, 1) = %b, %b", fa_y, fa_carry);
    
    a=1; b=0; cin=0; #10;
    if (ha_y !== 1'b1 || ha_carry !== 1'b0) $display("ERROR: HALF_ADDER(1, 0) = %b, %b", ha_y, ha_carry);
    if (fa_y !== 1'b1 || fa_carry !== 1'b0) $display("ERROR: fULL_ADDER(1, 0, 0) = %b, %b", fa_y, fa_carry);
    
    a=1; b=0; cin=1; #10;
    if (ha_y !== 1'b1 || ha_carry !== 1'b0) $display("ERROR: HALF_ADDER(1, 0) = %b, %b", ha_y, ha_carry);
    if (fa_y !== 1'b0 || fa_carry !== 1'b1) $display("ERROR: fULL_ADDER(1, 0, 1) = %b, %b", fa_y, fa_carry);
    
    a=1; b=1; cin=0; #10;
    if (ha_y !== 1'b0 || ha_carry !== 1'b1) $display("ERROR: HALF_ADDER(1, 1) = %b, %b", ha_y, ha_carry);
    if (fa_y !== 1'b0 || fa_carry !== 1'b1) $display("ERROR: fULL_ADDER(1, 1, 0) = %b, %b", fa_y, fa_carry);
    
    a=1; b=1; cin=1; #10;
    if (ha_y !== 1'b0 || ha_carry !== 1'b1) $display("ERROR: HALF_ADDER(1, 1) = %b, %b", ha_y, ha_carry);
    if (fa_y !== 1'b1 || fa_carry !== 1'b1) $display("ERROR: fULL_ADDER(1, 1, 1) = %b, %b", fa_y, fa_carry);
    
    $display("All adder tests passed");
  end

endmodule

// MUXES
module mux_2x1(
  input wire sel,
  input wire [1:0] data,
  output wire y
);

  wire not_sel;
  not_gate not1(
    .a(sel),
    .y(not_sel)
  );

  wire and_out1;
  wire and_out2;

  and_gate and1(
    .a(not_sel),
    .b(data[0]),
    .y(and_out1)
  );

  and_gate and2(
    .a(sel),
    .b(data[1]),
    .y(and_out2)
  );

  or_gate or1(
    .a(and_out1),
    .b(and_out2),
    .y(y)
  );

endmodule

module mux_4x1(
  input wire [1:0] sel,
  input wire [3:0] data,
  output wire y
);

  wire m1_out;
  wire m2_out;

  mux_2x1 m1(
    .sel(sel[0]),
    .data(data[1:0]),
    .y(m1_out)
  );

  mux_2x1 m2(
    .sel(sel[0]),
    .data(data[3:2]),
    .y(m2_out)
  );

  mux_2x1 m3(
    .sel(sel[1]),
    .data({m2_out, m1_out}),
    .y(y)
  );

endmodule

module mux_8x1(
  input wire [2:0] sel,
  input wire [7:0] data,
  output wire y
);

  wire m1_out;
  wire m2_out;

  mux_4x1 m1(
    .sel(sel[1:0]),
    .data(data[3:0]),
    .y(m1_out)
  );

  mux_4x1 m2(
    .sel(sel[1:0]),
    .data(data[7:4]),
    .y(m2_out)
  );

  mux_2x1 m3(
    .sel(sel[2]),
    .data({m2_out, m1_out}),
    .y(y)
  );

endmodule

// MUXES TESTS
module tb_muxes;

  reg [2:0] sel;
  reg [7:0] data;
  wire y2;
  wire y4;
  wire y8;

  mux_2x1 m1(
    .sel(sel[0]),
    .data(data[1:0]),
    .y(y2)
  );
  
  mux_4x1 m2(
    .sel(sel[1:0]),
    .data(data[3:0]),
    .y(y4)
  );
  
  mux_8x1 m3(
    .sel(sel),
    .data(data),
    .y(y8)
  );
  
  integer s;
  integer d;

  initial begin
    for (s = 0; s < 8; s = s + 1) begin
      for (d = 0; d < 256; d = d + 1) begin
        sel = s;
        data = d;
        #1;

        if (y2 !== data[sel[0]])   $display("ERROR MUX_2x1: sel=%b, data=%b, y=%b", sel[0], data[1:0], y2);
        if (y4 !== data[sel[1:0]]) $display("ERROR MUX_4x1: sel=%b, data=%b, y=%b", sel[1:0], data[3:0], y4);
        if (y8 !== data[sel])      $display("ERROR MUX_8x1: sel=%b, data=%b, y=%b", sel, data, y8);
      end
    end
  
    $display("All muxes tests passed");
  end

endmodule

// DEMUXES
module dmux_1x2(
  input wire sel,
  input wire data,
  output wire [1:0] y
);

  wire not_sel;
  not_gate not1(
    .a(sel),
    .y(not_sel)
  );

  and_gate and1(
    .a(not_sel),
    .b(data),
    .y(y[0])
  );

  and_gate and2(
    .a(sel),
    .b(data),
    .y(y[1])
  );

endmodule

module dmux_1x4(
  input wire [1:0] sel,
  input wire data,
  output wire [3:0] y  
);

  wire [1:0] dm1_out;

  dmux_1x2 dm1(
    .sel(sel[1]),
    .data(data),
    .y(dm1_out)
  );

  dmux_1x2 dm2(
    .sel(sel[0]),
    .data(dm1_out[0]),
    .y(y[1:0])
  );

  dmux_1x2 dm3(
    .sel(sel[0]),
    .data(dm1_out[1]),
    .y(y[3:2])
  );

endmodule

module dmux_1x8(
  input wire [2:0] sel,
  input wire data,
  output wire [7:0] y  
);

  wire [1:0] dm1_out;

  dmux_1x2 dm1(
    .sel(sel[2]),
    .data(data),
    .y(dm1_out)
  );

  dmux_1x4 dm2(
    .sel(sel[1:0]),
    .data(dm1_out[0]),
    .y(y[3:0])
  );

  dmux_1x4 dm3(
    .sel(sel[1:0]),
    .data(dm1_out[1]),
    .y(y[7:4])
  );

endmodule

// DEMUXES TESTS
module tb_dmuxes;

  reg [2:0] sel;
  reg data;
  wire [1:0] y2;
  wire [3:0] y4;
  wire [7:0] y8;

  dmux_1x2 dm1(
    .sel(sel[0]),
    .data(data),
    .y(y2)
  );

  dmux_1x4 dm2(
    .sel(sel[1:0]),
    .data(data),
    .y(y4)
  );

  dmux_1x8 dm3(
    .sel(sel),
    .data(data),
    .y(y8)
  );

  integer s;
  integer d;

  initial begin
  
    // test dmux_1x2
    for (s=0; s < 2; s= s + 1) begin
      for (d=0; d < 2; d = d + 1) begin
        sel = s;
        data = d;
        #1;

        if (y2 !== (d << s)) $display("ERROR DMUX_1x2: sel=%b, data=%b, y=%b", sel[0], data, y2);
      end
    end

    // test dmux_1x4
    for (s=0; s < 4; s= s + 1) begin
      for (d=0; d < 2; d = d + 1) begin
        sel = s;
        data = d;
        #1;

        if (y4 !== (d << s)) $display("ERROR DMUX_1x4: sel=%b, data=%b, y=%b", sel[1:0], data, y4);
      end
    end

    // test dmux_1x8
    for (s=0; s < 8; s= s + 1) begin
      for (d=0; d < 2; d = d + 1) begin
        sel = s;
        data = d;
        #1;

        if (y8 !== (d << s)) $display("ERROR DMUX_1x8: sel=%b, data=%b, y=%b", sel, data, y8);
      end
    end
  
    $display("All demuxes tests passed");
  end

endmodule

// BASIC OPERATIONS
module add8(
  input wire [7:0] a,
  input wire [7:0] b,
  output wire [7:0] y,
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
        .y(y[i]),
        .carry(temp_carry[i + 1])
      );
    end
  endgenerate

  assign carry = temp_carry[8];

endmodule

module sub8(
  input wire [7:0] a,
  input wire [7:0] b,
  output wire [7:0] y,
  output wire carry
);

  genvar i;
  wire [8:0] temp_carry;
  assign temp_carry[0] = 1'b1;

  wire [7:0] not_b;

  generate
    for (i = 0; i < 8; i = i + 1) begin
      not_gate not1(
        .a(b[i]),
        .y(not_b[i])
      );
    
      full_adder fa(
        .a(a[i]),
        .b(not_b[i]),
        .cin(temp_carry[i]),
        .y(y[i]),
        .carry(temp_carry[i + 1])
      );
    end
  endgenerate

  assign carry = temp_carry[8];

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
        .y(y[i]),
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
        .y(y[i]),
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
        .y(y[i]),
      );
    end
  endgenerate

endmodule

module not8(
  input wire [7:0] a,
  output wire [7:0] y
);

  genvar i;

  generate
    for (i = 0; i < 8; i = i + 1) begin
      not_gate not1(
        .a(a[i]),
        .y(y[i]),
      );
    end
  endgenerate

endmodule

module shl8(
  input wire [7:0] a,
  output wire [7:0] y,
  output wire carry
);

  genvar i;
  assign carry = a[7];

  generate
    for (i = 1; i < 8; i = i + 1) begin
      assign y[i] = a[i - 1];
    end
  endgenerate

  assign y[0] = 0;

endmodule

module shr8(
  input wire [7:0] a,
  output wire [7:0] y,
  output wire carry
);

  genvar i;
  assign carry = a[0];

  generate
    for (i = 0; i < 7; i= i + 1) begin
      assign y[i] = a[i + 1];
    end
  endgenerate

  assign y[7] = 0;

endmodule

// BASIC OPERATION TESTS
module tb_operations;

  reg [7:0] a;
  reg [7:0] b;
  wire [7:0] add_y;
  wire add_carry;

  wire [7:0] sub_y;
  wire sub_carry;

  wire [7:0] and_y;
  wire [7:0] or_y;
  wire [7:0] xor_y;
  wire [7:0] not_y;

  wire [7:0] shl_y;
  wire shl_carry;

  wire [7:0] shr_y;
  wire shr_carry;

  add8 add8_1(
    .a(a),
    .b(b),
    .y(add_y),
    .carry(add_carry)
  );

  sub8 sub8_1(
    .a(a),
    .b(b),
    .y(sub_y),
    .carry(sub_carry)
  );

  and8 and8_1(
    .a(a),
    .b(b),
    .y(and_y)
  );

  or8 or8_1(
    .a(a),
    .b(b),
    .y(or_y)
  );

  xor8 xor8_1(
    .a(a),
    .b(b),
    .y(xor_y)
  );

  not8 not8_1(
    .a(a),
    .y(not_y)
  );

  shl8 shl8_1(
    .a(a),
    .y(shl_y),
    .carry(shl_carry)
  );

  shr8 shr8_1(
    .a(a),
    .y(shr_y),
    .carry(shr_carry)
  );

  initial begin
  
    $display("All basic operation tests passed")
  end
  
endmodule

// COMBINED TESTS
module tb_tests;
  tb_gates gates();
  tb_adders adders();
  tb_muxes muxes();
  tb_dmuxes dmuxes();
  tb_operations operations();
endmodule
