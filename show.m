function show(img, width, height)
  f = fopen(img, "rb");
  img_src = fread(f, width * height, 'uint8');
  fclose(f);
  f = fopen(strcat(img, "_out"), "rb");
  img_dst = fread(f, width * height, 'uint8');
  fclose(f);

  img_src = reshape(img_src, [width, height])';
  img_dst = reshape(img_dst, [width, height])';

  subplot(1, 2, 1);
  imshow(img_src, []);
  title('Initial');
  subplot(1, 2, 2);
  imshow(img_dst, []);
  title('Sobel');

  pause(4);
end
