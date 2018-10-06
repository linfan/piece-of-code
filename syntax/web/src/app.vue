<style>
.literal-style {
    color: blue;
    font-style: italic;
}
.digital-style {
    color: green;
    font-weight: bold;
}
.keyword-style {
    color: mediumvioletred;
    font-weight: bold;
}
.primitive-type-style {
    color: darkgreen;
    font-weight: bold;
}
.constant-style {
    color: darkred;
    font-weight: bold;
}
.non-primitive-type-style {
    color: darkblue;
}
.double-quote-style {
    color: darkkhaki;
    font-weight: bold;
}
.single-quote-style {
    color: darkkhaki;
    font-weight: bold;
}
.multi-line-comment-style {
    color: yellowgreen;
}
.single-line-comment-style {
    color: yellowgreen;
}
.annotation-style {
    color: brown;
}
.field-style {
    color: purple;
    font-weight: bold;
}
.method-style {
    color: orange;
    font-weight: bold;
}
#code-area ol {
    font-family: "Consolas" , "Courier New" , Courier, mono, serif;
    font-size: 23px;
}
#code-area li div {
    display: inline;
}
#code-area li {
    padding-left: 1em;
}
#page-area {
    margin: 1em;
}
#upload-area > ul > li:not(:last-child), .el-icon-close, .el-icon-close-tip {
    display: none !important;
}
</style>

<template>
<div id="page-area">
    <el-upload
        id="upload-area"
        action="/api/highlight/java"
        :before-upload="beforeUpload"
        :on-success="onSuccess" >
        <el-button size="small" type="primary">点击上传</el-button>
        <div slot="tip" class="el-upload__tip">只能上传Java格式文件，且不超过2MB</div>
    </el-upload>
    <div id="code-area" v-html="highlightCode"></div>
</div>
</template>

<script>
export default {
    data() {
        return {
            highlightCode: ""
        }
    },
    methods: {
        beforeUpload(file) {
            const isJava = file.name.endsWith(".java");
            const isLt2M = file.size / 1024 / 1024 < 2;
            if (!isJava) {
              this.$message.error('只能上传 Java 格式文件!');
            }
            if (!isLt2M) {
              this.$message.error('上传文件不能超过 2MB!');
            }
            return isJava && isLt2M;
        },
        onSuccess(res, file, fileList) {
            this.highlightCode = res
        }
    }
}
</script>
