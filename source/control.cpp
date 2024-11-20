// #include "control.hpp"
// #include "polyPreset.cpp"

// static int tmp = 0;

// void m3_plot(int x, int y, COLOR clr)
// {	vid_mem[y*M3_WIDTH+x]= clr;	}

// INLINE void m4_plot(int x, int y, u8 clrid)
// {
// 	COLOR *dst= &vid_page[(y*M4_WIDTH+x)>>1];
// 	if(x&1)
// 		*dst= (*dst& 0xFF) | (clrid<<8);
// 	else
// 		*dst= (*dst&~0xFF) |  clrid;
// }



// control::control()
// {
    
//     objLen = 0;
//     floorLen = 0;
//     ceilLen = 0;

//     force = vec3::zero();
//     moveTMP = vec3::zero();
//     runSpeed = f32(20);
//     walkSpeed = f32(10);
//     jumpForce = f32(100);
//     gravity = f32(-10);
//     maxFallSpeed = f32(-30);
//     distance = f32(0);

//     jumped = false;

//     floorOP =f32(0.5f);
//     wallOP = f32(0.5f);
//     ceilOP = f32(0.5f);

//     clickJump = false;

//     polygonInit();
// }

// // void control::polygonInit()
// // {
    
// //     //mario.mesh = playerOBJ;
// //     mario.position = vec3({f32(0.0f), f32(10.0000f), f32(0.0f)});
// //     obj[0].mesh = wallOBJ;
// //     obj[0].position = vec3::zero();
// //     // obj[1].mesh = floorOBJ;
// //     // obj[1].position = vec3::zero();
// //     objLen = 1;
// //     for(int i = 0;i<objLen;i++)
// //     {
// //         object& tobj = obj[i];
// //         for(int j = 0;j<tobj.mesh.indexLen;j+=3)
// //         {
// //             Polygon poly;
// //             vec3 A = tobj.mesh.vertex[tobj.mesh.index[j]];
// //             vec3 B = tobj.mesh.vertex[tobj.mesh.index[j+1]];
// //             vec3 C = tobj.mesh.vertex[tobj.mesh.index[j+2]];
// //             // Check for potential zero-length vectors to prevent division by zero
// //             vec3 AB = A - B;
// //             vec3 BC = B - C;
// //             vec3 CA = A - C;

// //             if (length(AB) == 0 || length(BC) == 0 || length(CA) == 0) {
// //                 continue; // Skip degenerate triangles
// //             }

// //             poly.A = A;
// //             poly.B = B;
// //             poly.C = C;

// //             vec3 normal = cross(AB, BC);
// //             if (length(normal) == 0) {
// //                 continue; // Skip degenerate triangles with zero-area
// //             }

// //             poly.N = normalize(normal);
// //             poly.edge0 = normalize(cross(B - A, poly.N));
// //             poly.edge1 = normalize(cross(C - B, poly.N));
// //             poly.edge2 = normalize(cross(A - C, poly.N));
// //             poly.L = length(cross(AB, normalize(BC)));

// //             f32 d = dot(poly.N, vec3::UP());
// //             poly.dot = d;

            
// //             // if (d > f32(0.3f))
// //             // {
// //             //     floor[floorLen] = poly;
// //             //     floorLen++;
// //             // }
// //             // else if (d < f32(-0.3f))
// //             // {
// //             //     ceil[ceilLen] = poly;
// //             //     ceilLen++;
// //             // }
// //             // else
// //             // {
// //             //     wall[wallLen] = poly;
// //             //     wallLen++;
// //             // }
// //         }
// //     }
        
// // }
// void control::polygonInit()
// {
//     mario.position = vec3({f32(0.0f), f32(10.0000f), f32(0.0f)});

//     int len = polygonCount;
//     for(int i = 0;i<len;i++)
//     {
//         Polygon &poly = polygons[i];
//         if (poly.dot > f32(0.3f))
//         {
//             floor[floorLen] = poly;
//             floorLen++;
//         }
//         else if (poly.dot < f32(-0.3f))
//         {
//             ceil[ceilLen] = poly;
//             ceilLen++;
//         }
//         else
//         {
//             wall[wallLen] = poly;
//             wallLen++;
//         }
//     }
// }



// void control::playerControll()
// {
//     key_poll();
//     //updateDeltaTime();
//     moveTMP = vec3::zero();
//     f32 currentMoveSpeed = key_held(KEY_B) ? runSpeed : walkSpeed;
//     if(key_held(KEY_UP)) moveTMP = moveTMP + vec3::FRONT();
//     if(key_held(KEY_DOWN)) moveTMP = moveTMP + vec3::BACK();
//     if(key_held(KEY_RIGHT)) moveTMP = moveTMP + vec3::RIGHT();
//     if(key_held(KEY_LEFT)) moveTMP = moveTMP + vec3::LEFT();
//     moveTMP = moveTMP * currentMoveSpeed * deltaTime;
//     m4_plot(abs(int(mario.position.y)/100),abs(int(mario.position.y)%100),20);
//     if (!touchStatus[2])
//     {
//         m4_plot(int(mario.position.x)+50,int(mario.position.z)+50,20);
//         force.y += gravity * deltaTime;
//         force.y = max(force.y, maxFallSpeed);
//     }
//     else
//     {
//         m4_plot(int(mario.position.x)+50,int(mario.position.z)+50,5);
//         force.y = 0;
//         if (clickJump && !jumped)
//         {
            
//             clickJump = false;
//             touchStatus[2] = false;
//             jumped = true;
//             force.y = jumpForce;
//         }
        
//     }
    
// }



// bool control::trianglePrismTest(Polygon tri, vec3 pos)
// {
//     vec3 V = pos - tri.A;
//     f32 OP = f32(0.2f);
//     // m4_plot(int(OP * f32(10)),25,11);
//     // m4_plot(int(dot(V, tri.edge0) * f32(10)),30,20);
//     // m4_plot(int(dot(V, tri.edge2) * f32(10)),35,10);
//     // m4_plot(int((dot(V, tri.edge1)-tri.L) * f32(10)),40,20);
//     if ((dot(V, tri.edge0) < OP) && (dot(V, tri.edge2) < OP) && ((dot(V, tri.edge1) - tri.L) < OP))
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
    
// }

// bool control::normalTest(Polygon tri, vec3 pos, vec3 axis, f32 OP)
// {
//     vec3 V = pos - tri.A;
//     f32 height = dot(tri.N, V);
//     f32 hypot = dot(tri.N, axis);
//     //distance = divide(height , hypot);
//     distance = height / hypot;
//     //m4_plot(abs(int(distance)%100)+10,abs(int(distance))/100,10);
    
//     if (height <= OP && height >= f32(0))
//     {
        
//         return true;
//     }
//     else
//         return false;
// }

// void control::wallcheck(vec3& pos)
// {
//     for(int i = 0;i<wallLen;i++)
//     {
//         vec3 axis = wall[i].N;
//         axis.y = 0;
//         axis = normalize(axis);
        
//         if(trianglePrismTest(wall[i],pos) && normalTest(wall[i],pos,axis,wallOP))
//         {
            
//             if(distance <wallOP)
//             {
//                 m4_plot(tmp++ + 10,25,10);
//                 pos = pos + (axis * (wallOP - distance));
//             }
//         }
//     }
// }

// bool control::floorcheck(vec3& pos)
// {
//     vec3 axis = vec3::UP();
//     bool flag = false;
    
//     for(int i = 0;i<floorLen;i++)
//     {
        
//         if (trianglePrismTest(floor[i], pos)&&normalTest(floor[i], pos, axis, floorOP))
//         {
//             if (distance < floorOP)
//             {
//                 pos = pos + (axis * (floorOP - distance));
//                 flag = true;
//             }
//         }
//     }
//     return flag;
// }

// bool control::ceilcheck(vec3& pos)
// {
//     vec3 axis = vec3::DOWN();
//     for(int i = 0;i<ceilLen;i++)
//     {
        
//         if (trianglePrismTest(ceil[i], pos)&&normalTest(ceil[i], pos, axis, ceilOP))
//         {
//             if (distance < ceilOP)
//             {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// void control::checkCollision()
// {
//     //updateDeltaTime();
//     vec3 npos = mario.position + moveTMP + force * deltaTime;
    
//     wallcheck(npos);
//     if (floorcheck(npos))
//     {
        
//         jumped = false;
//         touchStatus[2] = true;
//     }
//     else 
//     {
//         //m4_plot(10,10,5);
//         touchStatus[2] = false;
//     }

//     if(ceilcheck(npos))
//     {
//         force.y = 0;
//         return;
//     }
//     mario.position = npos;
// }