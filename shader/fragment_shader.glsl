    #version 330 core
    in vec2 TexCoord;
    
    out vec4 FragColor;

    uniform sampler2D ourTexture;
    uniform sampler2D ourTexture1;
    uniform sampler2D ourTexture2;
    uniform sampler2D ourTexture3;

    // 区域划分阈值（根据需求调整）
    const float XedgeThreshold = 0.4; 
    const float YedgeThreshold = 0.3;

    //旋转和平移

    void main()
    {

        FragColor = texture(ourTexture, TexCoord);  
        /*
        bool Left = TexCoord.x < XedgeThreshold;
        bool Right = TexCoord.x > (1 - XedgeThreshold);
        bool Bottom = TexCoord.y < YedgeThreshold;
        bool Top = TexCoord.y > (1 - YedgeThreshold);


        if (TexCoord.y < 0.275) 
        {
            FragColor = texture(ourTexture2, vec2(TexCoord.x, TexCoord.y / 0.275));
        } else if (TexCoord.y > 0.725)
        {
            FragColor = texture(ourTexture, vec2(TexCoord.x, (TexCoord.y - 0.725) / 0.275));
        } else if (TexCoord.x < 0.375)
        {
            FragColor = texture(ourTexture1, vec2(TexCoord.x / 0.375, TexCoord.y));
        } else if (TexCoord.x > 0.625)
        {
            FragColor = texture(ourTexture3, vec2((TexCoord.x - 0.625) / 0.375, TexCoord.y));
        }
        else 
        {
            // 中间间隔部分，设置为透明或者某种背景颜色
            FragColor = vec4(0.0, 0.0, 0.0, 0.0); // 这里设置为透明
        } */
        
    }