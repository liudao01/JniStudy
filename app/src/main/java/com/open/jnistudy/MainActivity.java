package com.open.jnistudy;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.DividerItemDecoration;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.chad.library.adapter.base.BaseQuickAdapter;
import com.open.jnistudy.adapter.HomeAdapter;
import com.open.jnistudy.bean.ActivityBean;
import com.open.jnistudy.util.LogUtil;
import com.open.jnistudy.util.ToastUtils;

import java.util.ArrayList;
import java.util.Random;

/**
 * https://developer.android.com/studio/projects/add-native-code.html
 * 向您的项目添加 C 和 C++ 代码
 * <p>
 * https://github.com/android/ndk-samples/blob/main/hello-jni/app/src/main/cpp/hello-jni.c
 * 谷歌NDK示例代码
 */
public class MainActivity extends AppCompatActivity {
    private RecyclerView recyclerview;

    ToastUtils toastUtils;
    ArrayList<ActivityBean> list = new ArrayList<>();

    private String key = "keyValue";//java层定义的变量
    private static int count = 6;//java层定义的静态变量

    // 加载native库
    static {
        System.loadLibrary("native-lib");
    }

    HomeAdapter homeAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        toastUtils = new ToastUtils(this);
        recyclerview = findViewById(R.id.recyclerview);
        recyclerview.setLayoutManager(new LinearLayoutManager(this));
        //添加Android自带的分割线
        recyclerview.addItemDecoration(new DividerItemDecoration(this, DividerItemDecoration.VERTICAL));

        list.add(new ActivityBean(0, "jni静态注册并调用c方法", null));
        //访问非静态域
        list.add(new ActivityBean(1, "访问非静态域,c调用java修改变量", null));
        list.add(new ActivityBean(2, "访问静态域,c调用java修改静态变量", null));
        list.add(new ActivityBean(3, "c调用java非静态方法传入参数并获得返回值", null));

        homeAdapter = new HomeAdapter(R.layout.home_item_view, list);
        recyclerview.setAdapter(homeAdapter);

        homeAdapter.setOnItemClickListener(new BaseQuickAdapter.OnItemClickListener() {
            @Override
            public void onItemClick(BaseQuickAdapter adapter, View view, int position) {
                myOnclick(position);
            }
        });
    }

    private void myOnclick(int item) {
        MainActivity mainActivity = new MainActivity();
        switch (item) {
            case 0:
                toastUtils.showLongToast("java调用c++返回: " + stringFromJNI());
                break;
            case 1:
                LogUtil.d("改变之前的key" + mainActivity.key);
                toastUtils.showLongToast("原来java变量: " + key);
                mainActivity.accessField();
                LogUtil.d("改变之后的key" + mainActivity.key);
                toastUtils.showLongToast("c++修改java变量: " + key);
                break;
            case 2:
                LogUtil.d("改变之前的key" + count);
                toastUtils.showLongToast("原来java变量: " + count);
                mainActivity.accessStaticField();
                LogUtil.d("改变之后的key" + count);
                toastUtils.showLongToast("c++修改java静态变量: " + count);
                break;
            case 3:
                //c调用
                mainActivity.accessMethod();
                break;
        }
    }


    /**
     * java层非静态方法 获取随机数
     *
     * @param max
     * @return
     */
    int getRandeomInt(int max) {
        return new Random().nextInt(max);
    }


    /********定义native方法*****/
    /**
     * 创建一个静态方法,java调用c 返回一个字符串.
     */
    public native String stringFromJNI();

    public native String accessField();

    public native String accessStaticField();

    //c 调用 非静态 java 方法
    public native void accessMethod();


}
